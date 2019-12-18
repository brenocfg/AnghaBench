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
typedef  int /*<<< orphan*/  time_t ;
typedef  int /*<<< orphan*/  sebuf ;
struct TYPE_4__ {scalar_t__ sock; int /*<<< orphan*/  errorMessage; scalar_t__ ssl_in_use; } ;
typedef  TYPE_1__ PGconn ;

/* Variables and functions */
 scalar_t__ EINTR ; 
 scalar_t__ PGINVALID_SOCKET ; 
 int PG_STRERROR_R_BUFLEN ; 
 scalar_t__ SOCK_ERRNO ; 
 int /*<<< orphan*/  SOCK_STRERROR (scalar_t__,char*,int) ; 
 int /*<<< orphan*/  libpq_gettext (char*) ; 
 scalar_t__ pgtls_read_pending (TYPE_1__*) ; 
 int pqSocketPoll (scalar_t__,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printfPQExpBuffer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static int
pqSocketCheck(PGconn *conn, int forRead, int forWrite, time_t end_time)
{
	int			result;

	if (!conn)
		return -1;
	if (conn->sock == PGINVALID_SOCKET)
	{
		printfPQExpBuffer(&conn->errorMessage,
						  libpq_gettext("invalid socket\n"));
		return -1;
	}

#ifdef USE_SSL
	/* Check for SSL library buffering read bytes */
	if (forRead && conn->ssl_in_use && pgtls_read_pending(conn))
	{
		/* short-circuit the select */
		return 1;
	}
#endif

	/* We will retry as long as we get EINTR */
	do
		result = pqSocketPoll(conn->sock, forRead, forWrite, end_time);
	while (result < 0 && SOCK_ERRNO == EINTR);

	if (result < 0)
	{
		char		sebuf[PG_STRERROR_R_BUFLEN];

		printfPQExpBuffer(&conn->errorMessage,
						  libpq_gettext("select() failed: %s\n"),
						  SOCK_STRERROR(SOCK_ERRNO, sebuf, sizeof(sebuf)));
	}

	return result;
}