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
typedef  scalar_t__ int32 ;
typedef  int /*<<< orphan*/  QueuePosition ;
typedef  scalar_t__ BackendId ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  AsyncQueueLock ; 
 int /*<<< orphan*/  DEBUG3 ; 
 scalar_t__ InvalidPid ; 
 int /*<<< orphan*/  LWLockAcquire (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWLockRelease (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LW_EXCLUSIVE ; 
 int MaxBackends ; 
 scalar_t__ MyDatabaseId ; 
 scalar_t__ MyProcPid ; 
 int /*<<< orphan*/  PROCSIG_NOTIFY_INTERRUPT ; 
 scalar_t__ QUEUE_BACKEND_DBOID (scalar_t__) ; 
 scalar_t__ QUEUE_BACKEND_PID (scalar_t__) ; 
 int /*<<< orphan*/  QUEUE_BACKEND_POS (scalar_t__) ; 
 scalar_t__ QUEUE_CLEANUP_DELAY ; 
 scalar_t__ QUEUE_FIRST_LISTENER ; 
 int /*<<< orphan*/  QUEUE_HEAD ; 
 scalar_t__ QUEUE_NEXT_LISTENER (scalar_t__) ; 
 scalar_t__ QUEUE_POS_EQUAL (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QUEUE_POS_PAGE (int /*<<< orphan*/ ) ; 
 scalar_t__ SendProcSignal (scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ asyncQueuePageDiff (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 scalar_t__ palloc (int) ; 
 int /*<<< orphan*/  pfree (scalar_t__*) ; 

__attribute__((used)) static void
SignalBackends(void)
{
	int32	   *pids;
	BackendId  *ids;
	int			count;

	/*
	 * Identify backends that we need to signal.  We don't want to send
	 * signals while holding the AsyncQueueLock, so this loop just builds a
	 * list of target PIDs.
	 *
	 * XXX in principle these pallocs could fail, which would be bad. Maybe
	 * preallocate the arrays?	But in practice this is only run in trivial
	 * transactions, so there should surely be space available.
	 */
	pids = (int32 *) palloc(MaxBackends * sizeof(int32));
	ids = (BackendId *) palloc(MaxBackends * sizeof(BackendId));
	count = 0;

	LWLockAcquire(AsyncQueueLock, LW_EXCLUSIVE);
	for (BackendId i = QUEUE_FIRST_LISTENER; i > 0; i = QUEUE_NEXT_LISTENER(i))
	{
		int32		pid = QUEUE_BACKEND_PID(i);
		QueuePosition pos;

		Assert(pid != InvalidPid);
		if (pid == MyProcPid)
			continue;			/* never signal self */
		pos = QUEUE_BACKEND_POS(i);
		if (QUEUE_BACKEND_DBOID(i) == MyDatabaseId)
		{
			/*
			 * Always signal listeners in our own database, unless they're
			 * already caught up (unlikely, but possible).
			 */
			if (QUEUE_POS_EQUAL(pos, QUEUE_HEAD))
				continue;
		}
		else
		{
			/*
			 * Listeners in other databases should be signaled only if they
			 * are far behind.
			 */
			if (asyncQueuePageDiff(QUEUE_POS_PAGE(QUEUE_HEAD),
								   QUEUE_POS_PAGE(pos)) < QUEUE_CLEANUP_DELAY)
				continue;
		}
		/* OK, need to signal this one */
		pids[count] = pid;
		ids[count] = i;
		count++;
	}
	LWLockRelease(AsyncQueueLock);

	/* Now send signals */
	for (int i = 0; i < count; i++)
	{
		int32		pid = pids[i];

		/*
		 * Note: assuming things aren't broken, a signal failure here could
		 * only occur if the target backend exited since we released
		 * AsyncQueueLock; which is unlikely but certainly possible. So we
		 * just log a low-level debug message if it happens.
		 */
		if (SendProcSignal(pid, PROCSIG_NOTIFY_INTERRUPT, ids[i]) < 0)
			elog(DEBUG3, "could not signal backend with PID %d: %m", pid);
	}

	pfree(pids);
	pfree(ids);
}