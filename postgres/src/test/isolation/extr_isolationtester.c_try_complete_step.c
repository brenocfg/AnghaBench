#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct timeval {int tv_usec; scalar_t__ tv_sec; } ;
typedef  int /*<<< orphan*/  pidstring ;
typedef  int int64 ;
typedef  int /*<<< orphan*/  fd_set ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_10__ {int nsessions; TYPE_1__** sessions; } ;
typedef  TYPE_2__ TestSpec ;
struct TYPE_12__ {scalar_t__ be_pid; char* relname; char* extra; } ;
struct TYPE_11__ {int session; char* name; char* sql; char* errormsg; } ;
struct TYPE_9__ {char* name; } ;
typedef  TYPE_3__ Step ;
typedef  int /*<<< orphan*/  PGresult ;
typedef  TYPE_4__ PGnotify ;
typedef  int /*<<< orphan*/  PGconn ;
typedef  int /*<<< orphan*/  PGcancel ;

/* Variables and functions */
 scalar_t__ EINTR ; 
 int /*<<< orphan*/  FD_SET (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FD_ZERO (int /*<<< orphan*/ *) ; 
#define  PGRES_COMMAND_OK 130 
#define  PGRES_FATAL_ERROR 129 
#define  PGRES_TUPLES_OK 128 
 int /*<<< orphan*/  PG_DIAG_MESSAGE_PRIMARY ; 
 int /*<<< orphan*/  PG_DIAG_SEVERITY ; 
 scalar_t__ PQcancel (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  PQclear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PQconsumeInput (int /*<<< orphan*/ *) ; 
 char* PQerrorMessage (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PQexecPrepared (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PQfreeCancel (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PQfreemem (TYPE_4__*) ; 
 int /*<<< orphan*/ * PQgetCancel (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PQgetResult (int /*<<< orphan*/ *) ; 
 char* PQgetvalue (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ PQisBusy (int /*<<< orphan*/ *) ; 
 TYPE_4__* PQnotifies (int /*<<< orphan*/ *) ; 
 int PQntuples (int /*<<< orphan*/ *) ; 
 char* PQresStatus (int) ; 
 char* PQresultErrorField (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PQresultErrorMessage (int /*<<< orphan*/ *) ; 
 int PQresultStatus (int /*<<< orphan*/ *) ; 
 int PQsocket (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PREP_WAITING ; 
 int STEP_NONBLOCK ; 
 int STEP_RETRY ; 
 int USECS_PER_SEC ; 
 int /*<<< orphan*/ * backend_pid_strs ; 
 scalar_t__* backend_pids ; 
 int /*<<< orphan*/ ** conns ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  gettimeofday (struct timeval*,int /*<<< orphan*/ *) ; 
 char* pg_strdup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printResultSet (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 char* psprintf (char*,char const*,char const*) ; 
 int select (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct timeval*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,scalar_t__) ; 
 int /*<<< orphan*/  stderr ; 
 char* strerror (scalar_t__) ; 

__attribute__((used)) static bool
try_complete_step(TestSpec *testspec, Step *step, int flags)
{
	PGconn	   *conn = conns[1 + step->session];
	fd_set		read_set;
	struct timeval start_time;
	struct timeval timeout;
	int			sock = PQsocket(conn);
	int			ret;
	PGresult   *res;
	PGnotify   *notify;
	bool		canceled = false;

	if (sock < 0)
	{
		fprintf(stderr, "invalid socket: %s", PQerrorMessage(conn));
		exit(1);
	}

	gettimeofday(&start_time, NULL);
	FD_ZERO(&read_set);

	while (PQisBusy(conn))
	{
		FD_SET(sock, &read_set);
		timeout.tv_sec = 0;
		timeout.tv_usec = 10000;	/* Check for lock waits every 10ms. */

		ret = select(sock + 1, &read_set, NULL, NULL, &timeout);
		if (ret < 0)			/* error in select() */
		{
			if (errno == EINTR)
				continue;
			fprintf(stderr, "select failed: %s\n", strerror(errno));
			exit(1);
		}
		else if (ret == 0)		/* select() timeout: check for lock wait */
		{
			struct timeval current_time;
			int64		td;

			/* If it's OK for the step to block, check whether it has. */
			if (flags & STEP_NONBLOCK)
			{
				bool		waiting;

				res = PQexecPrepared(conns[0], PREP_WAITING, 1,
									 &backend_pid_strs[step->session + 1],
									 NULL, NULL, 0);
				if (PQresultStatus(res) != PGRES_TUPLES_OK ||
					PQntuples(res) != 1)
				{
					fprintf(stderr, "lock wait query failed: %s",
							PQerrorMessage(conns[0]));
					exit(1);
				}
				waiting = ((PQgetvalue(res, 0, 0))[0] == 't');
				PQclear(res);

				if (waiting)	/* waiting to acquire a lock */
				{
					/*
					 * Since it takes time to perform the lock-check query,
					 * some data --- notably, NOTICE messages --- might have
					 * arrived since we looked.  We must call PQconsumeInput
					 * and then PQisBusy to collect and process any such
					 * messages.  In the (unlikely) case that PQisBusy then
					 * returns false, we might as well go examine the
					 * available result.
					 */
					if (!PQconsumeInput(conn))
					{
						fprintf(stderr, "PQconsumeInput failed: %s\n",
								PQerrorMessage(conn));
						exit(1);
					}
					if (!PQisBusy(conn))
						break;

					/*
					 * conn is still busy, so conclude that the step really is
					 * waiting.
					 */
					if (!(flags & STEP_RETRY))
						printf("step %s: %s <waiting ...>\n",
							   step->name, step->sql);
					return true;
				}
				/* else, not waiting */
			}

			/* Figure out how long we've been waiting for this step. */
			gettimeofday(&current_time, NULL);
			td = (int64) current_time.tv_sec - (int64) start_time.tv_sec;
			td *= USECS_PER_SEC;
			td += (int64) current_time.tv_usec - (int64) start_time.tv_usec;

			/*
			 * After 180 seconds, try to cancel the query.
			 *
			 * If the user tries to test an invalid permutation, we don't want
			 * to hang forever, especially when this is running in the
			 * buildfarm.  This will presumably lead to this permutation
			 * failing, but remaining permutations and tests should still be
			 * OK.
			 */
			if (td > 180 * USECS_PER_SEC && !canceled)
			{
				PGcancel   *cancel = PQgetCancel(conn);

				if (cancel != NULL)
				{
					char		buf[256];

					if (PQcancel(cancel, buf, sizeof(buf)))
						canceled = true;
					else
						fprintf(stderr, "PQcancel failed: %s\n", buf);
					PQfreeCancel(cancel);
				}
			}

			/*
			 * After 200 seconds, just give up and die.
			 *
			 * Since cleanup steps won't be run in this case, this may cause
			 * later tests to fail.  That stinks, but it's better than waiting
			 * forever for the server to respond to the cancel.
			 */
			if (td > 200 * USECS_PER_SEC)
			{
				fprintf(stderr, "step %s timed out after 200 seconds\n",
						step->name);
				exit(1);
			}
		}
		else if (!PQconsumeInput(conn)) /* select(): data available */
		{
			fprintf(stderr, "PQconsumeInput failed: %s\n",
					PQerrorMessage(conn));
			exit(1);
		}
	}

	if (flags & STEP_RETRY)
		printf("step %s: <... completed>\n", step->name);
	else
		printf("step %s: %s\n", step->name, step->sql);

	while ((res = PQgetResult(conn)))
	{
		switch (PQresultStatus(res))
		{
			case PGRES_COMMAND_OK:
				break;
			case PGRES_TUPLES_OK:
				printResultSet(res);
				break;
			case PGRES_FATAL_ERROR:
				if (step->errormsg != NULL)
				{
					printf("WARNING: this step had a leftover error message\n");
					printf("%s\n", step->errormsg);
				}

				/*
				 * Detail may contain XID values, so we want to just show
				 * primary.  Beware however that libpq-generated error results
				 * may not contain subfields, only an old-style message.
				 */
				{
					const char *sev = PQresultErrorField(res,
														 PG_DIAG_SEVERITY);
					const char *msg = PQresultErrorField(res,
														 PG_DIAG_MESSAGE_PRIMARY);

					if (sev && msg)
						step->errormsg = psprintf("%s:  %s", sev, msg);
					else
						step->errormsg = pg_strdup(PQresultErrorMessage(res));
				}
				break;
			default:
				printf("unexpected result status: %s\n",
					   PQresStatus(PQresultStatus(res)));
		}
		PQclear(res);
	}

	/* Report any available NOTIFY messages, too */
	PQconsumeInput(conn);
	while ((notify = PQnotifies(conn)) != NULL)
	{
		/* Try to identify which session it came from */
		const char *sendername = NULL;
		char		pidstring[32];

		for (int i = 0; i < testspec->nsessions; i++)
		{
			if (notify->be_pid == backend_pids[i + 1])
			{
				sendername = testspec->sessions[i]->name;
				break;
			}
		}
		if (sendername == NULL)
		{
			/* Doesn't seem to be any test session, so show the hard way */
			snprintf(pidstring, sizeof(pidstring), "PID %d", notify->be_pid);
			sendername = pidstring;
		}
		printf("%s: NOTIFY \"%s\" with payload \"%s\" from %s\n",
			   testspec->sessions[step->session]->name,
			   notify->relname, notify->extra, sendername);
		PQfreemem(notify);
		PQconsumeInput(conn);
	}

	return false;
}