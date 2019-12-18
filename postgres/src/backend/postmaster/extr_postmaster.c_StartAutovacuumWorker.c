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
struct TYPE_4__ {int dead_end; int bgworker_notify; scalar_t__ pid; int /*<<< orphan*/  child_slot; int /*<<< orphan*/  elem; int /*<<< orphan*/  bkend_type; int /*<<< orphan*/  cancel_key; } ;
typedef  TYPE_1__ Backend ;

/* Variables and functions */
 int /*<<< orphan*/  AssignPostmasterChildSlot () ; 
 scalar_t__ AutoVacPID ; 
 int /*<<< orphan*/  AutoVacWorkerFailed () ; 
 int /*<<< orphan*/  BACKEND_TYPE_AUTOVAC ; 
 int /*<<< orphan*/  BackendList ; 
 scalar_t__ CAC_OK ; 
 int /*<<< orphan*/  ERRCODE_INTERNAL_ERROR ; 
 int /*<<< orphan*/  ERRCODE_OUT_OF_MEMORY ; 
 int /*<<< orphan*/  LOG ; 
 int /*<<< orphan*/  MyCancelKey ; 
 int /*<<< orphan*/  MyPMChildSlot ; 
 int /*<<< orphan*/  RandomCancelKey (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ReleasePostmasterChildSlot (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ShmemBackendArrayAdd (TYPE_1__*) ; 
 scalar_t__ StartAutoVacWorker () ; 
 int avlauncher_needs_signal ; 
 scalar_t__ canAcceptConnections (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dlist_push_head (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 scalar_t__ malloc (int) ; 

__attribute__((used)) static void
StartAutovacuumWorker(void)
{
	Backend    *bn;

	/*
	 * If not in condition to run a process, don't try, but handle it like a
	 * fork failure.  This does not normally happen, since the signal is only
	 * supposed to be sent by autovacuum launcher when it's OK to do it, but
	 * we have to check to avoid race-condition problems during DB state
	 * changes.
	 */
	if (canAcceptConnections(BACKEND_TYPE_AUTOVAC) == CAC_OK)
	{
		/*
		 * Compute the cancel key that will be assigned to this session. We
		 * probably don't need cancel keys for autovac workers, but we'd
		 * better have something random in the field to prevent unfriendly
		 * people from sending cancels to them.
		 */
		if (!RandomCancelKey(&MyCancelKey))
		{
			ereport(LOG,
					(errcode(ERRCODE_INTERNAL_ERROR),
					 errmsg("could not generate random cancel key")));
			return;
		}

		bn = (Backend *) malloc(sizeof(Backend));
		if (bn)
		{
			bn->cancel_key = MyCancelKey;

			/* Autovac workers are not dead_end and need a child slot */
			bn->dead_end = false;
			bn->child_slot = MyPMChildSlot = AssignPostmasterChildSlot();
			bn->bgworker_notify = false;

			bn->pid = StartAutoVacWorker();
			if (bn->pid > 0)
			{
				bn->bkend_type = BACKEND_TYPE_AUTOVAC;
				dlist_push_head(&BackendList, &bn->elem);
#ifdef EXEC_BACKEND
				ShmemBackendArrayAdd(bn);
#endif
				/* all OK */
				return;
			}

			/*
			 * fork failed, fall through to report -- actual error message was
			 * logged by StartAutoVacWorker
			 */
			(void) ReleasePostmasterChildSlot(bn->child_slot);
			free(bn);
		}
		else
			ereport(LOG,
					(errcode(ERRCODE_OUT_OF_MEMORY),
					 errmsg("out of memory")));
	}

	/*
	 * Report the failure to the launcher, if it's running.  (If it's not, we
	 * might not even be connected to shared memory, so don't try to call
	 * AutoVacWorkerFailed.)  Note that we also need to signal it so that it
	 * responds to the condition, but we don't do that here, instead waiting
	 * for ServerLoop to do it.  This way we avoid a ping-pong signalling in
	 * quick succession between the autovac launcher and postmaster in case
	 * things get ugly.
	 */
	if (AutoVacPID != 0)
	{
		AutoVacWorkerFailed();
		avlauncher_needs_signal = true;
	}
}