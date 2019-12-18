#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct sockaddr {int dummy; } ;
typedef  int /*<<< orphan*/  pgsocket ;
typedef  int /*<<< orphan*/  on ;
typedef  int /*<<< orphan*/  oldopt ;
typedef  int /*<<< orphan*/  newopt ;
struct TYPE_11__ {int /*<<< orphan*/  ss_family; } ;
struct TYPE_12__ {int salen; TYPE_2__ addr; } ;
struct TYPE_10__ {int salen; int /*<<< orphan*/  addr; } ;
struct TYPE_13__ {int /*<<< orphan*/  sock; TYPE_3__ laddr; TYPE_1__ raddr; } ;
typedef  TYPE_4__ Port ;

/* Variables and functions */
 int /*<<< orphan*/  IPPROTO_TCP ; 
 int /*<<< orphan*/  IS_AF_UNIX (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOG ; 
 int /*<<< orphan*/  PGINVALID_SOCKET ; 
 int PQ_SEND_BUFFER_SIZE ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_KEEPALIVE ; 
 int /*<<< orphan*/  SO_SNDBUF ; 
 int STATUS_ERROR ; 
 int STATUS_OK ; 
 int /*<<< orphan*/  TCP_NODELAY ; 
 int /*<<< orphan*/  accept (int /*<<< orphan*/ ,struct sockaddr*,int*) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode_for_socket_access () ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 scalar_t__ getsockname (int /*<<< orphan*/ ,struct sockaddr*,int*) ; 
 scalar_t__ getsockopt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int*) ; 
 int /*<<< orphan*/  pg_usleep (long) ; 
 int /*<<< orphan*/  pq_setkeepalivescount (int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  pq_setkeepalivesidle (int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  pq_setkeepalivesinterval (int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  pq_settcpusertimeout (int /*<<< orphan*/ ,TYPE_4__*) ; 
 scalar_t__ setsockopt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  tcp_keepalives_count ; 
 int /*<<< orphan*/  tcp_keepalives_idle ; 
 int /*<<< orphan*/  tcp_keepalives_interval ; 
 int /*<<< orphan*/  tcp_user_timeout ; 

int
StreamConnection(pgsocket server_fd, Port *port)
{
	/* accept connection and fill in the client (remote) address */
	port->raddr.salen = sizeof(port->raddr.addr);
	if ((port->sock = accept(server_fd,
							 (struct sockaddr *) &port->raddr.addr,
							 &port->raddr.salen)) == PGINVALID_SOCKET)
	{
		ereport(LOG,
				(errcode_for_socket_access(),
				 errmsg("could not accept new connection: %m")));

		/*
		 * If accept() fails then postmaster.c will still see the server
		 * socket as read-ready, and will immediately try again.  To avoid
		 * uselessly sucking lots of CPU, delay a bit before trying again.
		 * (The most likely reason for failure is being out of kernel file
		 * table slots; we can do little except hope some will get freed up.)
		 */
		pg_usleep(100000L);		/* wait 0.1 sec */
		return STATUS_ERROR;
	}

	/* fill in the server (local) address */
	port->laddr.salen = sizeof(port->laddr.addr);
	if (getsockname(port->sock,
					(struct sockaddr *) &port->laddr.addr,
					&port->laddr.salen) < 0)
	{
		elog(LOG, "getsockname() failed: %m");
		return STATUS_ERROR;
	}

	/* select NODELAY and KEEPALIVE options if it's a TCP connection */
	if (!IS_AF_UNIX(port->laddr.addr.ss_family))
	{
		int			on;
#ifdef WIN32
		int			oldopt;
		int			optlen;
		int			newopt;
#endif

#ifdef	TCP_NODELAY
		on = 1;
		if (setsockopt(port->sock, IPPROTO_TCP, TCP_NODELAY,
					   (char *) &on, sizeof(on)) < 0)
		{
			elog(LOG, "setsockopt(%s) failed: %m", "TCP_NODELAY");
			return STATUS_ERROR;
		}
#endif
		on = 1;
		if (setsockopt(port->sock, SOL_SOCKET, SO_KEEPALIVE,
					   (char *) &on, sizeof(on)) < 0)
		{
			elog(LOG, "setsockopt(%s) failed: %m", "SO_KEEPALIVE");
			return STATUS_ERROR;
		}

#ifdef WIN32

		/*
		 * This is a Win32 socket optimization.  The OS send buffer should be
		 * large enough to send the whole Postgres send buffer in one go, or
		 * performance suffers.  The Postgres send buffer can be enlarged if a
		 * very large message needs to be sent, but we won't attempt to
		 * enlarge the OS buffer if that happens, so somewhat arbitrarily
		 * ensure that the OS buffer is at least PQ_SEND_BUFFER_SIZE * 4.
		 * (That's 32kB with the current default).
		 *
		 * The default OS buffer size used to be 8kB in earlier Windows
		 * versions, but was raised to 64kB in Windows 2012.  So it shouldn't
		 * be necessary to change it in later versions anymore.  Changing it
		 * unnecessarily can even reduce performance, because setting
		 * SO_SNDBUF in the application disables the "dynamic send buffering"
		 * feature that was introduced in Windows 7.  So before fiddling with
		 * SO_SNDBUF, check if the current buffer size is already large enough
		 * and only increase it if necessary.
		 *
		 * See https://support.microsoft.com/kb/823764/EN-US/ and
		 * https://msdn.microsoft.com/en-us/library/bb736549%28v=vs.85%29.aspx
		 */
		optlen = sizeof(oldopt);
		if (getsockopt(port->sock, SOL_SOCKET, SO_SNDBUF, (char *) &oldopt,
					   &optlen) < 0)
		{
			elog(LOG, "getsockopt(%s) failed: %m", "SO_SNDBUF");
			return STATUS_ERROR;
		}
		newopt = PQ_SEND_BUFFER_SIZE * 4;
		if (oldopt < newopt)
		{
			if (setsockopt(port->sock, SOL_SOCKET, SO_SNDBUF, (char *) &newopt,
						   sizeof(newopt)) < 0)
			{
				elog(LOG, "setsockopt(%s) failed: %m", "SO_SNDBUF");
				return STATUS_ERROR;
			}
		}
#endif

		/*
		 * Also apply the current keepalive parameters.  If we fail to set a
		 * parameter, don't error out, because these aren't universally
		 * supported.  (Note: you might think we need to reset the GUC
		 * variables to 0 in such a case, but it's not necessary because the
		 * show hooks for these variables report the truth anyway.)
		 */
		(void) pq_setkeepalivesidle(tcp_keepalives_idle, port);
		(void) pq_setkeepalivesinterval(tcp_keepalives_interval, port);
		(void) pq_setkeepalivescount(tcp_keepalives_count, port);
		(void) pq_settcpusertimeout(tcp_user_timeout, port);
	}

	return STATUS_OK;
}