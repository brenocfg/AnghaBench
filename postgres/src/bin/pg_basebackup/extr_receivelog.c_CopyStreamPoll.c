#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct timeval {long tv_sec; long tv_usec; } ;
typedef  int pgsocket ;
typedef  int /*<<< orphan*/  fd_set ;
typedef  int /*<<< orphan*/  PGconn ;

/* Variables and functions */
 scalar_t__ EINTR ; 
 scalar_t__ FD_ISSET (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FD_SET (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FD_ZERO (int /*<<< orphan*/ *) ; 
 int Max (int,int) ; 
 int PGINVALID_SOCKET ; 
 int /*<<< orphan*/  PQerrorMessage (int /*<<< orphan*/ *) ; 
 int PQsocket (int /*<<< orphan*/ *) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  pg_log_error (char*,...) ; 
 int select (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct timeval*) ; 

__attribute__((used)) static int
CopyStreamPoll(PGconn *conn, long timeout_ms, pgsocket stop_socket)
{
	int			ret;
	fd_set		input_mask;
	int			connsocket;
	int			maxfd;
	struct timeval timeout;
	struct timeval *timeoutptr;

	connsocket = PQsocket(conn);
	if (connsocket < 0)
	{
		pg_log_error("invalid socket: %s", PQerrorMessage(conn));
		return -1;
	}

	FD_ZERO(&input_mask);
	FD_SET(connsocket, &input_mask);
	maxfd = connsocket;
	if (stop_socket != PGINVALID_SOCKET)
	{
		FD_SET(stop_socket, &input_mask);
		maxfd = Max(maxfd, stop_socket);
	}

	if (timeout_ms < 0)
		timeoutptr = NULL;
	else
	{
		timeout.tv_sec = timeout_ms / 1000L;
		timeout.tv_usec = (timeout_ms % 1000L) * 1000L;
		timeoutptr = &timeout;
	}

	ret = select(maxfd + 1, &input_mask, NULL, NULL, timeoutptr);

	if (ret < 0)
	{
		if (errno == EINTR)
			return 0;			/* Got a signal, so not an error */
		pg_log_error("select() failed: %m");
		return -1;
	}
	if (ret > 0 && FD_ISSET(connsocket, &input_mask))
		return 1;				/* Got input on connection socket */

	return 0;					/* Got timeout or input on stop_socket */
}