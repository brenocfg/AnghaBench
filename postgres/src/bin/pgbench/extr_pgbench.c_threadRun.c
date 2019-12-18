#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  socket_set ;
typedef  int /*<<< orphan*/  logpath ;
typedef  int int64 ;
typedef  int /*<<< orphan*/  instr_time ;
struct TYPE_10__ {scalar_t__ state; int sleep_until; int txn_scheduled; int /*<<< orphan*/ * con; } ;
struct TYPE_9__ {int nstate; scalar_t__ tid; int /*<<< orphan*/ * logfile; int /*<<< orphan*/  conn_time; int /*<<< orphan*/  start_time; void* throttle_trigger; TYPE_2__* state; } ;
typedef  TYPE_1__ TState ;
typedef  int /*<<< orphan*/  StatsData ;
typedef  TYPE_2__ CState ;

/* Variables and functions */
 scalar_t__ CSTATE_ABORTED ; 
 scalar_t__ CSTATE_CHOOSE_SCRIPT ; 
 scalar_t__ CSTATE_FINISHED ; 
 scalar_t__ CSTATE_SLEEP ; 
 scalar_t__ CSTATE_THROTTLE ; 
 scalar_t__ CSTATE_WAIT_RESULT ; 
 scalar_t__ EINTR ; 
 int /*<<< orphan*/  INSTR_TIME_ACCUM_DIFF (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* INSTR_TIME_GET_MICROSEC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INSTR_TIME_SET_CURRENT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INSTR_TIME_SET_ZERO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INSTR_TIME_SUBTRACT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int MAXPGPATH ; 
 int PG_INT64_MAX ; 
 char* PQerrorMessage (int /*<<< orphan*/ *) ; 
 int PQsocket (int /*<<< orphan*/ *) ; 
 char* SOCKET_WAIT_METHOD ; 
 int /*<<< orphan*/  add_socket_to_set (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  advanceConnectionState (TYPE_1__*,TYPE_2__*,int /*<<< orphan*/ *) ; 
 scalar_t__ agg_interval ; 
 int /*<<< orphan*/ * alloc_socket_set (int) ; 
 int /*<<< orphan*/  clear_socket_set (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  disconnect_all (TYPE_2__*,int) ; 
 int /*<<< orphan*/ * doConnect () ; 
 int /*<<< orphan*/  doLog (TYPE_1__*,TYPE_2__*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,...) ; 
 int /*<<< orphan*/  free_socket_set (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  initStats (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_connect ; 
 char* logfile_prefix ; 
 int main_pid ; 
 int /*<<< orphan*/  pg_usleep (int) ; 
 int /*<<< orphan*/  printProgressReport (TYPE_1__*,int,int,int /*<<< orphan*/ *,int*) ; 
 scalar_t__ progress ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,int,...) ; 
 int /*<<< orphan*/  socket_has_input (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 char* strerror (scalar_t__) ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 
 scalar_t__ use_log ; 
 int wait_on_socket_set (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void *
threadRun(void *arg)
{
	TState	   *thread = (TState *) arg;
	CState	   *state = thread->state;
	instr_time	start,
				end;
	int			nstate = thread->nstate;
	int			remains = nstate;	/* number of remaining clients */
	socket_set *sockets = alloc_socket_set(nstate);
	int			i;

	/* for reporting progress: */
	int64		thread_start = INSTR_TIME_GET_MICROSEC(thread->start_time);
	int64		last_report = thread_start;
	int64		next_report = last_report + (int64) progress * 1000000;
	StatsData	last,
				aggs;

	/*
	 * Initialize throttling rate target for all of the thread's clients.  It
	 * might be a little more accurate to reset thread->start_time here too.
	 * The possible drift seems too small relative to typical throttle delay
	 * times to worry about it.
	 */
	INSTR_TIME_SET_CURRENT(start);
	thread->throttle_trigger = INSTR_TIME_GET_MICROSEC(start);

	INSTR_TIME_SET_ZERO(thread->conn_time);

	initStats(&aggs, time(NULL));
	last = aggs;

	/* open log file if requested */
	if (use_log)
	{
		char		logpath[MAXPGPATH];
		char	   *prefix = logfile_prefix ? logfile_prefix : "pgbench_log";

		if (thread->tid == 0)
			snprintf(logpath, sizeof(logpath), "%s.%d", prefix, main_pid);
		else
			snprintf(logpath, sizeof(logpath), "%s.%d.%d", prefix, main_pid, thread->tid);

		thread->logfile = fopen(logpath, "w");

		if (thread->logfile == NULL)
		{
			fprintf(stderr, "could not open logfile \"%s\": %s\n",
					logpath, strerror(errno));
			goto done;
		}
	}

	if (!is_connect)
	{
		/* make connections to the database before starting */
		for (i = 0; i < nstate; i++)
		{
			if ((state[i].con = doConnect()) == NULL)
				goto done;
		}
	}

	/* time after thread and connections set up */
	INSTR_TIME_SET_CURRENT(thread->conn_time);
	INSTR_TIME_SUBTRACT(thread->conn_time, thread->start_time);

	/* explicitly initialize the state machines */
	for (i = 0; i < nstate; i++)
	{
		state[i].state = CSTATE_CHOOSE_SCRIPT;
	}

	/* loop till all clients have terminated */
	while (remains > 0)
	{
		int			nsocks;		/* number of sockets to be waited for */
		int64		min_usec;
		int64		now_usec = 0;	/* set this only if needed */

		/*
		 * identify which client sockets should be checked for input, and
		 * compute the nearest time (if any) at which we need to wake up.
		 */
		clear_socket_set(sockets);
		nsocks = 0;
		min_usec = PG_INT64_MAX;
		for (i = 0; i < nstate; i++)
		{
			CState	   *st = &state[i];

			if (st->state == CSTATE_SLEEP || st->state == CSTATE_THROTTLE)
			{
				/* a nap from the script, or under throttling */
				int64		this_usec;

				/* get current time if needed */
				if (now_usec == 0)
				{
					instr_time	now;

					INSTR_TIME_SET_CURRENT(now);
					now_usec = INSTR_TIME_GET_MICROSEC(now);
				}

				/* min_usec should be the minimum delay across all clients */
				this_usec = (st->state == CSTATE_SLEEP ?
							 st->sleep_until : st->txn_scheduled) - now_usec;
				if (min_usec > this_usec)
					min_usec = this_usec;
			}
			else if (st->state == CSTATE_WAIT_RESULT)
			{
				/*
				 * waiting for result from server - nothing to do unless the
				 * socket is readable
				 */
				int			sock = PQsocket(st->con);

				if (sock < 0)
				{
					fprintf(stderr, "invalid socket: %s",
							PQerrorMessage(st->con));
					goto done;
				}

				add_socket_to_set(sockets, sock, nsocks++);
			}
			else if (st->state != CSTATE_ABORTED &&
					 st->state != CSTATE_FINISHED)
			{
				/*
				 * This client thread is ready to do something, so we don't
				 * want to wait.  No need to examine additional clients.
				 */
				min_usec = 0;
				break;
			}
		}

		/* also wake up to print the next progress report on time */
		if (progress && min_usec > 0 && thread->tid == 0)
		{
			/* get current time if needed */
			if (now_usec == 0)
			{
				instr_time	now;

				INSTR_TIME_SET_CURRENT(now);
				now_usec = INSTR_TIME_GET_MICROSEC(now);
			}

			if (now_usec >= next_report)
				min_usec = 0;
			else if ((next_report - now_usec) < min_usec)
				min_usec = next_report - now_usec;
		}

		/*
		 * If no clients are ready to execute actions, sleep until we receive
		 * data on some client socket or the timeout (if any) elapses.
		 */
		if (min_usec > 0)
		{
			int			rc = 0;

			if (min_usec != PG_INT64_MAX)
			{
				if (nsocks > 0)
				{
					rc = wait_on_socket_set(sockets, min_usec);
				}
				else			/* nothing active, simple sleep */
				{
					pg_usleep(min_usec);
				}
			}
			else				/* no explicit delay, wait without timeout */
			{
				rc = wait_on_socket_set(sockets, 0);
			}

			if (rc < 0)
			{
				if (errno == EINTR)
				{
					/* On EINTR, go back to top of loop */
					continue;
				}
				/* must be something wrong */
				fprintf(stderr, "%s() failed: %s\n", SOCKET_WAIT_METHOD, strerror(errno));
				goto done;
			}
		}
		else
		{
			/* min_usec <= 0, i.e. something needs to be executed now */

			/* If we didn't wait, don't try to read any data */
			clear_socket_set(sockets);
		}

		/* ok, advance the state machine of each connection */
		nsocks = 0;
		for (i = 0; i < nstate; i++)
		{
			CState	   *st = &state[i];

			if (st->state == CSTATE_WAIT_RESULT)
			{
				/* don't call advanceConnectionState unless data is available */
				int			sock = PQsocket(st->con);

				if (sock < 0)
				{
					fprintf(stderr, "invalid socket: %s",
							PQerrorMessage(st->con));
					goto done;
				}

				if (!socket_has_input(sockets, sock, nsocks++))
					continue;
			}
			else if (st->state == CSTATE_FINISHED ||
					 st->state == CSTATE_ABORTED)
			{
				/* this client is done, no need to consider it anymore */
				continue;
			}

			advanceConnectionState(thread, st, &aggs);

			/*
			 * If advanceConnectionState changed client to finished state,
			 * that's one less client that remains.
			 */
			if (st->state == CSTATE_FINISHED || st->state == CSTATE_ABORTED)
				remains--;
		}

		/* progress report is made by thread 0 for all threads */
		if (progress && thread->tid == 0)
		{
			instr_time	now_time;
			int64		now;

			INSTR_TIME_SET_CURRENT(now_time);
			now = INSTR_TIME_GET_MICROSEC(now_time);
			if (now >= next_report)
			{
				/*
				 * Horrible hack: this relies on the thread pointer we are
				 * passed to be equivalent to threads[0], that is the first
				 * entry of the threads array.  That is why this MUST be done
				 * by thread 0 and not any other.
				 */
				printProgressReport(thread, thread_start, now,
									&last, &last_report);

				/*
				 * Ensure that the next report is in the future, in case
				 * pgbench/postgres got stuck somewhere.
				 */
				do
				{
					next_report += (int64) progress * 1000000;
				} while (now >= next_report);
			}
		}
	}

done:
	INSTR_TIME_SET_CURRENT(start);
	disconnect_all(state, nstate);
	INSTR_TIME_SET_CURRENT(end);
	INSTR_TIME_ACCUM_DIFF(thread->conn_time, end, start);
	if (thread->logfile)
	{
		if (agg_interval > 0)
		{
			/* log aggregated but not yet reported transactions */
			doLog(thread, state, &aggs, false, 0, 0);
		}
		fclose(thread->logfile);
		thread->logfile = NULL;
	}
	free_socket_set(sockets);
	return NULL;
}