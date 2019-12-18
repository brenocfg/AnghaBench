#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int dead_end; int bgworker_notify; int /*<<< orphan*/  child_slot; int /*<<< orphan*/  bkend_type; int /*<<< orphan*/  cancel_key; } ;
struct TYPE_5__ {int /*<<< orphan*/  rw_child_slot; TYPE_2__* rw_backend; } ;
typedef  TYPE_1__ RegisteredBgWorker ;
typedef  TYPE_2__ Backend ;

/* Variables and functions */
 int /*<<< orphan*/  AssignPostmasterChildSlot () ; 
 int /*<<< orphan*/  BACKEND_TYPE_BGWORKER ; 
 scalar_t__ CAC_OK ; 
 int /*<<< orphan*/  ERRCODE_CONFIGURATION_LIMIT_EXCEEDED ; 
 int /*<<< orphan*/  ERRCODE_INTERNAL_ERROR ; 
 int /*<<< orphan*/  ERRCODE_OUT_OF_MEMORY ; 
 int /*<<< orphan*/  LOG ; 
 int /*<<< orphan*/  MyCancelKey ; 
 int /*<<< orphan*/  MyPMChildSlot ; 
 int /*<<< orphan*/  RandomCancelKey (int /*<<< orphan*/ *) ; 
 scalar_t__ canAcceptConnections (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 TYPE_2__* malloc (int) ; 

__attribute__((used)) static bool
assign_backendlist_entry(RegisteredBgWorker *rw)
{
	Backend    *bn;

	/*
	 * Check that database state allows another connection.  Currently the
	 * only possible failure is CAC_TOOMANY, so we just log an error message
	 * based on that rather than checking the error code precisely.
	 */
	if (canAcceptConnections(BACKEND_TYPE_BGWORKER) != CAC_OK)
	{
		ereport(LOG,
				(errcode(ERRCODE_CONFIGURATION_LIMIT_EXCEEDED),
				 errmsg("no slot available for new worker process")));
		return false;
	}

	/*
	 * Compute the cancel key that will be assigned to this session. We
	 * probably don't need cancel keys for background workers, but we'd better
	 * have something random in the field to prevent unfriendly people from
	 * sending cancels to them.
	 */
	if (!RandomCancelKey(&MyCancelKey))
	{
		ereport(LOG,
				(errcode(ERRCODE_INTERNAL_ERROR),
				 errmsg("could not generate random cancel key")));
		return false;
	}

	bn = malloc(sizeof(Backend));
	if (bn == NULL)
	{
		ereport(LOG,
				(errcode(ERRCODE_OUT_OF_MEMORY),
				 errmsg("out of memory")));
		return false;
	}

	bn->cancel_key = MyCancelKey;
	bn->child_slot = MyPMChildSlot = AssignPostmasterChildSlot();
	bn->bkend_type = BACKEND_TYPE_BGWORKER;
	bn->dead_end = false;
	bn->bgworker_notify = false;

	rw->rw_backend = bn;
	rw->rw_child_slot = bn->child_slot;

	return true;
}