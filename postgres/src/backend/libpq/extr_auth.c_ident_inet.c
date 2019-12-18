#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct addrinfo {scalar_t__ ai_addrlen; int /*<<< orphan*/ * ai_addr; scalar_t__ ai_protocol; void* ai_socktype; int /*<<< orphan*/  ai_family; int /*<<< orphan*/ * ai_next; int /*<<< orphan*/ * ai_canonname; void* ai_flags; } ;
typedef  int /*<<< orphan*/  remote_port ;
typedef  int /*<<< orphan*/  remote_addr_s ;
typedef  scalar_t__ pgsocket ;
typedef  int /*<<< orphan*/  local_port ;
typedef  int /*<<< orphan*/  local_addr_s ;
typedef  int /*<<< orphan*/  ident_response ;
typedef  int /*<<< orphan*/  ident_query ;
typedef  int /*<<< orphan*/  ident_port ;
struct TYPE_9__ {int /*<<< orphan*/  ss_family; } ;
struct TYPE_8__ {TYPE_4__ addr; int /*<<< orphan*/  salen; } ;
struct TYPE_7__ {int /*<<< orphan*/  user_name; TYPE_1__* hba; TYPE_3__ laddr; TYPE_3__ raddr; } ;
typedef  TYPE_2__ hbaPort ;
struct TYPE_6__ {int /*<<< orphan*/  usermap; } ;
typedef  TYPE_3__ SockAddr ;

/* Variables and functions */
 void* AI_NUMERICHOST ; 
 int /*<<< orphan*/  CHECK_FOR_INTERRUPTS () ; 
 scalar_t__ EINTR ; 
 int IDENT_PORT ; 
 int /*<<< orphan*/  IDENT_USERNAME_MAX ; 
 int /*<<< orphan*/  LOG ; 
 int NI_MAXHOST ; 
 int NI_MAXSERV ; 
 int NI_NUMERICHOST ; 
 int NI_NUMERICSERV ; 
 scalar_t__ PGINVALID_SOCKET ; 
 void* SOCK_STREAM ; 
 int STATUS_ERROR ; 
 int bind (scalar_t__,int /*<<< orphan*/ *,scalar_t__) ; 
 int check_usermap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  closesocket (scalar_t__) ; 
 int connect (scalar_t__,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode_for_socket_access () ; 
 int /*<<< orphan*/  errmsg (char*,...) ; 
 scalar_t__ errno ; 
 int interpret_ident_response (char*,char*) ; 
 int /*<<< orphan*/  pg_freeaddrinfo_all (int /*<<< orphan*/ ,struct addrinfo*) ; 
 int pg_getaddrinfo_all (char*,char*,struct addrinfo*,struct addrinfo**) ; 
 int /*<<< orphan*/  pg_getnameinfo_all (TYPE_4__*,int /*<<< orphan*/ ,char*,int,char*,int,int) ; 
 int recv (scalar_t__,char*,int,int /*<<< orphan*/ ) ; 
 int send (scalar_t__,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,...) ; 
 scalar_t__ socket (int /*<<< orphan*/ ,void*,scalar_t__) ; 
 int /*<<< orphan*/  strlen (char*) ; 

__attribute__((used)) static int
ident_inet(hbaPort *port)
{
	const SockAddr remote_addr = port->raddr;
	const SockAddr local_addr = port->laddr;
	char		ident_user[IDENT_USERNAME_MAX + 1];
	pgsocket	sock_fd = PGINVALID_SOCKET; /* for talking to Ident server */
	int			rc;				/* Return code from a locally called function */
	bool		ident_return;
	char		remote_addr_s[NI_MAXHOST];
	char		remote_port[NI_MAXSERV];
	char		local_addr_s[NI_MAXHOST];
	char		local_port[NI_MAXSERV];
	char		ident_port[NI_MAXSERV];
	char		ident_query[80];
	char		ident_response[80 + IDENT_USERNAME_MAX];
	struct addrinfo *ident_serv = NULL,
			   *la = NULL,
				hints;

	/*
	 * Might look a little weird to first convert it to text and then back to
	 * sockaddr, but it's protocol independent.
	 */
	pg_getnameinfo_all(&remote_addr.addr, remote_addr.salen,
					   remote_addr_s, sizeof(remote_addr_s),
					   remote_port, sizeof(remote_port),
					   NI_NUMERICHOST | NI_NUMERICSERV);
	pg_getnameinfo_all(&local_addr.addr, local_addr.salen,
					   local_addr_s, sizeof(local_addr_s),
					   local_port, sizeof(local_port),
					   NI_NUMERICHOST | NI_NUMERICSERV);

	snprintf(ident_port, sizeof(ident_port), "%d", IDENT_PORT);
	hints.ai_flags = AI_NUMERICHOST;
	hints.ai_family = remote_addr.addr.ss_family;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = 0;
	hints.ai_addrlen = 0;
	hints.ai_canonname = NULL;
	hints.ai_addr = NULL;
	hints.ai_next = NULL;
	rc = pg_getaddrinfo_all(remote_addr_s, ident_port, &hints, &ident_serv);
	if (rc || !ident_serv)
	{
		/* we don't expect this to happen */
		ident_return = false;
		goto ident_inet_done;
	}

	hints.ai_flags = AI_NUMERICHOST;
	hints.ai_family = local_addr.addr.ss_family;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = 0;
	hints.ai_addrlen = 0;
	hints.ai_canonname = NULL;
	hints.ai_addr = NULL;
	hints.ai_next = NULL;
	rc = pg_getaddrinfo_all(local_addr_s, NULL, &hints, &la);
	if (rc || !la)
	{
		/* we don't expect this to happen */
		ident_return = false;
		goto ident_inet_done;
	}

	sock_fd = socket(ident_serv->ai_family, ident_serv->ai_socktype,
					 ident_serv->ai_protocol);
	if (sock_fd == PGINVALID_SOCKET)
	{
		ereport(LOG,
				(errcode_for_socket_access(),
				 errmsg("could not create socket for Ident connection: %m")));
		ident_return = false;
		goto ident_inet_done;
	}

	/*
	 * Bind to the address which the client originally contacted, otherwise
	 * the ident server won't be able to match up the right connection. This
	 * is necessary if the PostgreSQL server is running on an IP alias.
	 */
	rc = bind(sock_fd, la->ai_addr, la->ai_addrlen);
	if (rc != 0)
	{
		ereport(LOG,
				(errcode_for_socket_access(),
				 errmsg("could not bind to local address \"%s\": %m",
						local_addr_s)));
		ident_return = false;
		goto ident_inet_done;
	}

	rc = connect(sock_fd, ident_serv->ai_addr,
				 ident_serv->ai_addrlen);
	if (rc != 0)
	{
		ereport(LOG,
				(errcode_for_socket_access(),
				 errmsg("could not connect to Ident server at address \"%s\", port %s: %m",
						remote_addr_s, ident_port)));
		ident_return = false;
		goto ident_inet_done;
	}

	/* The query we send to the Ident server */
	snprintf(ident_query, sizeof(ident_query), "%s,%s\r\n",
			 remote_port, local_port);

	/* loop in case send is interrupted */
	do
	{
		CHECK_FOR_INTERRUPTS();

		rc = send(sock_fd, ident_query, strlen(ident_query), 0);
	} while (rc < 0 && errno == EINTR);

	if (rc < 0)
	{
		ereport(LOG,
				(errcode_for_socket_access(),
				 errmsg("could not send query to Ident server at address \"%s\", port %s: %m",
						remote_addr_s, ident_port)));
		ident_return = false;
		goto ident_inet_done;
	}

	do
	{
		CHECK_FOR_INTERRUPTS();

		rc = recv(sock_fd, ident_response, sizeof(ident_response) - 1, 0);
	} while (rc < 0 && errno == EINTR);

	if (rc < 0)
	{
		ereport(LOG,
				(errcode_for_socket_access(),
				 errmsg("could not receive response from Ident server at address \"%s\", port %s: %m",
						remote_addr_s, ident_port)));
		ident_return = false;
		goto ident_inet_done;
	}

	ident_response[rc] = '\0';
	ident_return = interpret_ident_response(ident_response, ident_user);
	if (!ident_return)
		ereport(LOG,
				(errmsg("invalidly formatted response from Ident server: \"%s\"",
						ident_response)));

ident_inet_done:
	if (sock_fd != PGINVALID_SOCKET)
		closesocket(sock_fd);
	if (ident_serv)
		pg_freeaddrinfo_all(remote_addr.addr.ss_family, ident_serv);
	if (la)
		pg_freeaddrinfo_all(local_addr.addr.ss_family, la);

	if (ident_return)
		/* Success! Check the usermap */
		return check_usermap(port->hba->usermap, port->user_name, ident_user, false);
	return STATUS_ERROR;
}