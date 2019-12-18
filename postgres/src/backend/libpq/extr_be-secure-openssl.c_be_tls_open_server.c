#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int ssl_in_use; char* peer_cn; int peer_cert_valid; int /*<<< orphan*/ * peer; scalar_t__ ssl; int /*<<< orphan*/  sock; int /*<<< orphan*/  noblock; } ;
typedef  TYPE_1__ Port ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  COMMERROR ; 
 int /*<<< orphan*/  ERRCODE_PROTOCOL_VIOLATION ; 
 int /*<<< orphan*/  ERR_clear_error () ; 
 unsigned long ERR_get_error () ; 
 char* MemoryContextAlloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MyLatch ; 
 int /*<<< orphan*/  NID_commonName ; 
 int /*<<< orphan*/  SSL_CTX_set_info_callback (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  SSL_ERROR_SSL 132 
#define  SSL_ERROR_SYSCALL 131 
#define  SSL_ERROR_WANT_READ 130 
#define  SSL_ERROR_WANT_WRITE 129 
#define  SSL_ERROR_ZERO_RETURN 128 
 int SSL_accept (scalar_t__) ; 
 int /*<<< orphan*/  SSL_context ; 
 int SSL_get_error (scalar_t__,int) ; 
 int /*<<< orphan*/ * SSL_get_peer_certificate (scalar_t__) ; 
 scalar_t__ SSL_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSLerrmessage (unsigned long) ; 
 int /*<<< orphan*/  TopMemoryContext ; 
 int /*<<< orphan*/  WAIT_EVENT_SSL_OPEN_SERVER ; 
 int WL_EXIT_ON_PM_DEATH ; 
 int WL_SOCKET_READABLE ; 
 int WL_SOCKET_WRITEABLE ; 
 int /*<<< orphan*/  WaitLatchOrSocket (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int X509_NAME_get_text_by_NID (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  X509_get_subject_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode_for_socket_access () ; 
 int /*<<< orphan*/  errmsg (char*,...) ; 
 int /*<<< orphan*/  info_cb ; 
 int /*<<< orphan*/  my_SSL_set_fd (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pfree (char*) ; 
 int strlen (char*) ; 

int
be_tls_open_server(Port *port)
{
	int			r;
	int			err;
	int			waitfor;
	unsigned long ecode;

	Assert(!port->ssl);
	Assert(!port->peer);

	if (!SSL_context)
	{
		ereport(COMMERROR,
				(errcode(ERRCODE_PROTOCOL_VIOLATION),
				 errmsg("could not initialize SSL connection: SSL context not set up")));
		return -1;
	}

	if (!(port->ssl = SSL_new(SSL_context)))
	{
		ereport(COMMERROR,
				(errcode(ERRCODE_PROTOCOL_VIOLATION),
				 errmsg("could not initialize SSL connection: %s",
						SSLerrmessage(ERR_get_error()))));
		return -1;
	}
	if (!my_SSL_set_fd(port, port->sock))
	{
		ereport(COMMERROR,
				(errcode(ERRCODE_PROTOCOL_VIOLATION),
				 errmsg("could not set SSL socket: %s",
						SSLerrmessage(ERR_get_error()))));
		return -1;
	}
	port->ssl_in_use = true;

aloop:

	/*
	 * Prepare to call SSL_get_error() by clearing thread's OpenSSL error
	 * queue.  In general, the current thread's error queue must be empty
	 * before the TLS/SSL I/O operation is attempted, or SSL_get_error() will
	 * not work reliably.  An extension may have failed to clear the
	 * per-thread error queue following another call to an OpenSSL I/O
	 * routine.
	 */
	ERR_clear_error();
	r = SSL_accept(port->ssl);
	if (r <= 0)
	{
		err = SSL_get_error(port->ssl, r);

		/*
		 * Other clients of OpenSSL in the backend may fail to call
		 * ERR_get_error(), but we always do, so as to not cause problems for
		 * OpenSSL clients that don't call ERR_clear_error() defensively.  Be
		 * sure that this happens by calling now. SSL_get_error() relies on
		 * the OpenSSL per-thread error queue being intact, so this is the
		 * earliest possible point ERR_get_error() may be called.
		 */
		ecode = ERR_get_error();
		switch (err)
		{
			case SSL_ERROR_WANT_READ:
			case SSL_ERROR_WANT_WRITE:
				/* not allowed during connection establishment */
				Assert(!port->noblock);

				/*
				 * No need to care about timeouts/interrupts here. At this
				 * point authentication_timeout still employs
				 * StartupPacketTimeoutHandler() which directly exits.
				 */
				if (err == SSL_ERROR_WANT_READ)
					waitfor = WL_SOCKET_READABLE | WL_EXIT_ON_PM_DEATH;
				else
					waitfor = WL_SOCKET_WRITEABLE | WL_EXIT_ON_PM_DEATH;

				(void) WaitLatchOrSocket(MyLatch, waitfor, port->sock, 0,
										 WAIT_EVENT_SSL_OPEN_SERVER);
				goto aloop;
			case SSL_ERROR_SYSCALL:
				if (r < 0)
					ereport(COMMERROR,
							(errcode_for_socket_access(),
							 errmsg("could not accept SSL connection: %m")));
				else
					ereport(COMMERROR,
							(errcode(ERRCODE_PROTOCOL_VIOLATION),
							 errmsg("could not accept SSL connection: EOF detected")));
				break;
			case SSL_ERROR_SSL:
				ereport(COMMERROR,
						(errcode(ERRCODE_PROTOCOL_VIOLATION),
						 errmsg("could not accept SSL connection: %s",
								SSLerrmessage(ecode))));
				break;
			case SSL_ERROR_ZERO_RETURN:
				ereport(COMMERROR,
						(errcode(ERRCODE_PROTOCOL_VIOLATION),
						 errmsg("could not accept SSL connection: EOF detected")));
				break;
			default:
				ereport(COMMERROR,
						(errcode(ERRCODE_PROTOCOL_VIOLATION),
						 errmsg("unrecognized SSL error code: %d",
								err)));
				break;
		}
		return -1;
	}

	/* Get client certificate, if available. */
	port->peer = SSL_get_peer_certificate(port->ssl);

	/* and extract the Common Name from it. */
	port->peer_cn = NULL;
	port->peer_cert_valid = false;
	if (port->peer != NULL)
	{
		int			len;

		len = X509_NAME_get_text_by_NID(X509_get_subject_name(port->peer),
										NID_commonName, NULL, 0);
		if (len != -1)
		{
			char	   *peer_cn;

			peer_cn = MemoryContextAlloc(TopMemoryContext, len + 1);
			r = X509_NAME_get_text_by_NID(X509_get_subject_name(port->peer),
										  NID_commonName, peer_cn, len + 1);
			peer_cn[len] = '\0';
			if (r != len)
			{
				/* shouldn't happen */
				pfree(peer_cn);
				return -1;
			}

			/*
			 * Reject embedded NULLs in certificate common name to prevent
			 * attacks like CVE-2009-4034.
			 */
			if (len != strlen(peer_cn))
			{
				ereport(COMMERROR,
						(errcode(ERRCODE_PROTOCOL_VIOLATION),
						 errmsg("SSL certificate's common name contains embedded null")));
				pfree(peer_cn);
				return -1;
			}

			port->peer_cn = peer_cn;
		}
		port->peer_cert_valid = true;
	}

	/* set up debugging/info callback */
	SSL_CTX_set_info_callback(SSL_context, info_cb);

	return 0;
}