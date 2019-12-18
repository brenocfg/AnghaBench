#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int ckpt_failed; int ckpt_started; int ckpt_flags; scalar_t__ checkpointer_pid; int ckpt_done; int /*<<< orphan*/  done_cv; int /*<<< orphan*/  ckpt_lck; int /*<<< orphan*/  start_cv; } ;

/* Variables and functions */
 int CHECKPOINT_IMMEDIATE ; 
 int CHECKPOINT_REQUESTED ; 
 int CHECKPOINT_WAIT ; 
 int /*<<< orphan*/  CHECK_FOR_INTERRUPTS () ; 
 TYPE_1__* CheckpointerShmem ; 
 int /*<<< orphan*/  ConditionVariableCancelSleep () ; 
 int /*<<< orphan*/  ConditionVariablePrepareToSleep (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ConditionVariableSleep (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CreateCheckPoint (int) ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  IsPostmasterEnvironment ; 
 int /*<<< orphan*/  LOG ; 
 int MAX_SIGNAL_TRIES ; 
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  SpinLockAcquire (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SpinLockRelease (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WAIT_EVENT_CHECKPOINT_DONE ; 
 int /*<<< orphan*/  WAIT_EVENT_CHECKPOINT_START ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errhint (char*) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 scalar_t__ kill (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pg_usleep (long) ; 
 int /*<<< orphan*/  smgrcloseall () ; 

void
RequestCheckpoint(int flags)
{
	int			ntries;
	int			old_failed,
				old_started;

	/*
	 * If in a standalone backend, just do it ourselves.
	 */
	if (!IsPostmasterEnvironment)
	{
		/*
		 * There's no point in doing slow checkpoints in a standalone backend,
		 * because there's no other backends the checkpoint could disrupt.
		 */
		CreateCheckPoint(flags | CHECKPOINT_IMMEDIATE);

		/*
		 * After any checkpoint, close all smgr files.  This is so we won't
		 * hang onto smgr references to deleted files indefinitely.
		 */
		smgrcloseall();

		return;
	}

	/*
	 * Atomically set the request flags, and take a snapshot of the counters.
	 * When we see ckpt_started > old_started, we know the flags we set here
	 * have been seen by checkpointer.
	 *
	 * Note that we OR the flags with any existing flags, to avoid overriding
	 * a "stronger" request by another backend.  The flag senses must be
	 * chosen to make this work!
	 */
	SpinLockAcquire(&CheckpointerShmem->ckpt_lck);

	old_failed = CheckpointerShmem->ckpt_failed;
	old_started = CheckpointerShmem->ckpt_started;
	CheckpointerShmem->ckpt_flags |= (flags | CHECKPOINT_REQUESTED);

	SpinLockRelease(&CheckpointerShmem->ckpt_lck);

	/*
	 * Send signal to request checkpoint.  It's possible that the checkpointer
	 * hasn't started yet, or is in process of restarting, so we will retry a
	 * few times if needed.  (Actually, more than a few times, since on slow
	 * or overloaded buildfarm machines, it's been observed that the
	 * checkpointer can take several seconds to start.)  However, if not told
	 * to wait for the checkpoint to occur, we consider failure to send the
	 * signal to be nonfatal and merely LOG it.  The checkpointer should see
	 * the request when it does start, with or without getting a signal.
	 */
#define MAX_SIGNAL_TRIES 600	/* max wait 60.0 sec */
	for (ntries = 0;; ntries++)
	{
		if (CheckpointerShmem->checkpointer_pid == 0)
		{
			if (ntries >= MAX_SIGNAL_TRIES || !(flags & CHECKPOINT_WAIT))
			{
				elog((flags & CHECKPOINT_WAIT) ? ERROR : LOG,
					 "could not signal for checkpoint: checkpointer is not running");
				break;
			}
		}
		else if (kill(CheckpointerShmem->checkpointer_pid, SIGINT) != 0)
		{
			if (ntries >= MAX_SIGNAL_TRIES || !(flags & CHECKPOINT_WAIT))
			{
				elog((flags & CHECKPOINT_WAIT) ? ERROR : LOG,
					 "could not signal for checkpoint: %m");
				break;
			}
		}
		else
			break;				/* signal sent successfully */

		CHECK_FOR_INTERRUPTS();
		pg_usleep(100000L);		/* wait 0.1 sec, then retry */
	}

	/*
	 * If requested, wait for completion.  We detect completion according to
	 * the algorithm given above.
	 */
	if (flags & CHECKPOINT_WAIT)
	{
		int			new_started,
					new_failed;

		/* Wait for a new checkpoint to start. */
		ConditionVariablePrepareToSleep(&CheckpointerShmem->start_cv);
		for (;;)
		{
			SpinLockAcquire(&CheckpointerShmem->ckpt_lck);
			new_started = CheckpointerShmem->ckpt_started;
			SpinLockRelease(&CheckpointerShmem->ckpt_lck);

			if (new_started != old_started)
				break;

			ConditionVariableSleep(&CheckpointerShmem->start_cv,
								   WAIT_EVENT_CHECKPOINT_START);
		}
		ConditionVariableCancelSleep();

		/*
		 * We are waiting for ckpt_done >= new_started, in a modulo sense.
		 */
		ConditionVariablePrepareToSleep(&CheckpointerShmem->done_cv);
		for (;;)
		{
			int			new_done;

			SpinLockAcquire(&CheckpointerShmem->ckpt_lck);
			new_done = CheckpointerShmem->ckpt_done;
			new_failed = CheckpointerShmem->ckpt_failed;
			SpinLockRelease(&CheckpointerShmem->ckpt_lck);

			if (new_done - new_started >= 0)
				break;

			ConditionVariableSleep(&CheckpointerShmem->done_cv,
								   WAIT_EVENT_CHECKPOINT_DONE);
		}
		ConditionVariableCancelSleep();

		if (new_failed != old_failed)
			ereport(ERROR,
					(errmsg("checkpoint request failed"),
					 errhint("Consult recent messages in the server log for details.")));
	}
}