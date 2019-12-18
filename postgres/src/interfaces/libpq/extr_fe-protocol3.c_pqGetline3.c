#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ sock; scalar_t__ asyncStatus; int /*<<< orphan*/  errorMessage; scalar_t__ copy_is_binary; } ;
typedef  TYPE_1__ PGconn ;

/* Variables and functions */
 int EOF ; 
 scalar_t__ PGASYNC_COPY_BOTH ; 
 scalar_t__ PGASYNC_COPY_OUT ; 
 scalar_t__ PGINVALID_SOCKET ; 
 int PQgetlineAsync (TYPE_1__*,char*,int) ; 
 int /*<<< orphan*/  libpq_gettext (char*) ; 
 scalar_t__ pqReadData (TYPE_1__*) ; 
 scalar_t__ pqWait (int,int,TYPE_1__*) ; 
 int /*<<< orphan*/  printfPQExpBuffer (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 

int
pqGetline3(PGconn *conn, char *s, int maxlen)
{
	int			status;

	if (conn->sock == PGINVALID_SOCKET ||
		(conn->asyncStatus != PGASYNC_COPY_OUT &&
		 conn->asyncStatus != PGASYNC_COPY_BOTH) ||
		conn->copy_is_binary)
	{
		printfPQExpBuffer(&conn->errorMessage,
						  libpq_gettext("PQgetline: not doing text COPY OUT\n"));
		*s = '\0';
		return EOF;
	}

	while ((status = PQgetlineAsync(conn, s, maxlen - 1)) == 0)
	{
		/* need to load more data */
		if (pqWait(true, false, conn) ||
			pqReadData(conn) < 0)
		{
			*s = '\0';
			return EOF;
		}
	}

	if (status < 0)
	{
		/* End of copy detected; gin up old-style terminator */
		strcpy(s, "\\.");
		return 0;
	}

	/* Add null terminator, and strip trailing \n if present */
	if (s[status - 1] == '\n')
	{
		s[status - 1] = '\0';
		return 0;
	}
	else
	{
		s[status] = '\0';
		return 1;
	}
}