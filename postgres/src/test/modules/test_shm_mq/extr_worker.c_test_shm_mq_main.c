#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int workers_attached; int workers_total; int /*<<< orphan*/  mutex; int /*<<< orphan*/  workers_ready; } ;
typedef  TYPE_1__ test_shm_mq_header ;
typedef  int /*<<< orphan*/  shm_toc ;
typedef  int /*<<< orphan*/  shm_mq_handle ;
typedef  int /*<<< orphan*/  dsm_segment ;
struct TYPE_8__ {int /*<<< orphan*/  bgw_notify_pid; } ;
struct TYPE_7__ {int /*<<< orphan*/  procLatch; } ;
typedef  TYPE_2__ PGPROC ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 TYPE_2__* BackendPidGetProc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BackgroundWorkerUnblockSignals () ; 
 int /*<<< orphan*/  DEBUG1 ; 
 int /*<<< orphan*/  DatumGetInt32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERRCODE_OBJECT_NOT_IN_PREREQUISITE_STATE ; 
 int /*<<< orphan*/  ERROR ; 
 TYPE_4__* MyBgworkerEntry ; 
 int /*<<< orphan*/  PG_TEST_SHM_MQ_MAGIC ; 
 int /*<<< orphan*/  SIGTERM ; 
 int /*<<< orphan*/  SetLatch (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SpinLockAcquire (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SpinLockRelease (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  attach_to_queues (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ **,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  copy_messages (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dsm_attach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsm_detach (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dsm_segment_address (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 int /*<<< orphan*/  handle_sigterm ; 
 int /*<<< orphan*/  pqsignal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  proc_exit (int) ; 
 int /*<<< orphan*/ * shm_toc_attach (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* shm_toc_lookup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

void
test_shm_mq_main(Datum main_arg)
{
	dsm_segment *seg;
	shm_toc    *toc;
	shm_mq_handle *inqh;
	shm_mq_handle *outqh;
	volatile test_shm_mq_header *hdr;
	int			myworkernumber;
	PGPROC	   *registrant;

	/*
	 * Establish signal handlers.
	 *
	 * We want CHECK_FOR_INTERRUPTS() to kill off this worker process just as
	 * it would a normal user backend.  To make that happen, we establish a
	 * signal handler that is a stripped-down version of die().
	 */
	pqsignal(SIGTERM, handle_sigterm);
	BackgroundWorkerUnblockSignals();

	/*
	 * Connect to the dynamic shared memory segment.
	 *
	 * The backend that registered this worker passed us the ID of a shared
	 * memory segment to which we must attach for further instructions.  Once
	 * we've mapped the segment in our address space, attach to the table of
	 * contents so we can locate the various data structures we'll need to
	 * find within the segment.
	 *
	 * Note: at this point, we have not created any ResourceOwner in this
	 * process.  This will result in our DSM mapping surviving until process
	 * exit, which is fine.  If there were a ResourceOwner, it would acquire
	 * ownership of the mapping, but we have no need for that.
	 */
	seg = dsm_attach(DatumGetInt32(main_arg));
	if (seg == NULL)
		ereport(ERROR,
				(errcode(ERRCODE_OBJECT_NOT_IN_PREREQUISITE_STATE),
				 errmsg("unable to map dynamic shared memory segment")));
	toc = shm_toc_attach(PG_TEST_SHM_MQ_MAGIC, dsm_segment_address(seg));
	if (toc == NULL)
		ereport(ERROR,
				(errcode(ERRCODE_OBJECT_NOT_IN_PREREQUISITE_STATE),
				 errmsg("bad magic number in dynamic shared memory segment")));

	/*
	 * Acquire a worker number.
	 *
	 * By convention, the process registering this background worker should
	 * have stored the control structure at key 0.  We look up that key to
	 * find it.  Our worker number gives our identity: there may be just one
	 * worker involved in this parallel operation, or there may be many.
	 */
	hdr = shm_toc_lookup(toc, 0, false);
	SpinLockAcquire(&hdr->mutex);
	myworkernumber = ++hdr->workers_attached;
	SpinLockRelease(&hdr->mutex);
	if (myworkernumber > hdr->workers_total)
		ereport(ERROR,
				(errcode(ERRCODE_OBJECT_NOT_IN_PREREQUISITE_STATE),
				 errmsg("too many message queue testing workers already")));

	/*
	 * Attach to the appropriate message queues.
	 */
	attach_to_queues(seg, toc, myworkernumber, &inqh, &outqh);

	/*
	 * Indicate that we're fully initialized and ready to begin the main part
	 * of the parallel operation.
	 *
	 * Once we signal that we're ready, the user backend is entitled to assume
	 * that our on_dsm_detach callbacks will fire before we disconnect from
	 * the shared memory segment and exit.  Generally, that means we must have
	 * attached to all relevant dynamic shared memory data structures by now.
	 */
	SpinLockAcquire(&hdr->mutex);
	++hdr->workers_ready;
	SpinLockRelease(&hdr->mutex);
	registrant = BackendPidGetProc(MyBgworkerEntry->bgw_notify_pid);
	if (registrant == NULL)
	{
		elog(DEBUG1, "registrant backend has exited prematurely");
		proc_exit(1);
	}
	SetLatch(&registrant->procLatch);

	/* Do the work. */
	copy_messages(inqh, outqh);

	/*
	 * We're done.  For cleanliness, explicitly detach from the shared memory
	 * segment (that would happen anyway during process exit, though).
	 */
	dsm_detach(seg);
	proc_exit(1);
}