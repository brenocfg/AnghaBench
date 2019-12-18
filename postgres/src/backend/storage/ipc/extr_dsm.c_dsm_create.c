#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32 ;
struct TYPE_9__ {scalar_t__ mapped_size; scalar_t__ handle; size_t control_slot; int /*<<< orphan*/  node; int /*<<< orphan*/ * resowner; int /*<<< orphan*/ * mapped_address; int /*<<< orphan*/  impl_private; } ;
typedef  TYPE_2__ dsm_segment ;
struct TYPE_10__ {size_t nitems; size_t maxitems; TYPE_1__* item; } ;
struct TYPE_8__ {int refcnt; scalar_t__ handle; int pinned; int /*<<< orphan*/ * impl_private_pm_handle; } ;
typedef  int /*<<< orphan*/  Size ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int DSM_CREATE_NULL_IF_MAXSEGMENTS ; 
 scalar_t__ DSM_HANDLE_INVALID ; 
 int /*<<< orphan*/  DSM_OP_CREATE ; 
 int /*<<< orphan*/  DSM_OP_DESTROY ; 
 int /*<<< orphan*/  DynamicSharedMemoryControlLock ; 
 int /*<<< orphan*/  ERRCODE_INSUFFICIENT_RESOURCES ; 
 int /*<<< orphan*/  ERROR ; 
 int IsUnderPostmaster ; 
 int /*<<< orphan*/  LWLockAcquire (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWLockRelease (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LW_EXCLUSIVE ; 
 int /*<<< orphan*/  ResourceOwnerForgetDSM (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  WARNING ; 
 int /*<<< orphan*/  dlist_delete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dsm_backend_startup () ; 
 TYPE_6__* dsm_control ; 
 TYPE_2__* dsm_create_descriptor () ; 
 scalar_t__ dsm_impl_op (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsm_init_done ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 int /*<<< orphan*/  pfree (TYPE_2__*) ; 
 scalar_t__ random () ; 

dsm_segment *
dsm_create(Size size, int flags)
{
	dsm_segment *seg;
	uint32		i;
	uint32		nitems;

	/* Unsafe in postmaster (and pointless in a stand-alone backend). */
	Assert(IsUnderPostmaster);

	if (!dsm_init_done)
		dsm_backend_startup();

	/* Create a new segment descriptor. */
	seg = dsm_create_descriptor();

	/* Loop until we find an unused segment identifier. */
	for (;;)
	{
		Assert(seg->mapped_address == NULL && seg->mapped_size == 0);
		seg->handle = random();
		if (seg->handle == DSM_HANDLE_INVALID)	/* Reserve sentinel */
			continue;
		if (dsm_impl_op(DSM_OP_CREATE, seg->handle, size, &seg->impl_private,
						&seg->mapped_address, &seg->mapped_size, ERROR))
			break;
	}

	/* Lock the control segment so we can register the new segment. */
	LWLockAcquire(DynamicSharedMemoryControlLock, LW_EXCLUSIVE);

	/* Search the control segment for an unused slot. */
	nitems = dsm_control->nitems;
	for (i = 0; i < nitems; ++i)
	{
		if (dsm_control->item[i].refcnt == 0)
		{
			dsm_control->item[i].handle = seg->handle;
			/* refcnt of 1 triggers destruction, so start at 2 */
			dsm_control->item[i].refcnt = 2;
			dsm_control->item[i].impl_private_pm_handle = NULL;
			dsm_control->item[i].pinned = false;
			seg->control_slot = i;
			LWLockRelease(DynamicSharedMemoryControlLock);
			return seg;
		}
	}

	/* Verify that we can support an additional mapping. */
	if (nitems >= dsm_control->maxitems)
	{
		if ((flags & DSM_CREATE_NULL_IF_MAXSEGMENTS) != 0)
		{
			LWLockRelease(DynamicSharedMemoryControlLock);
			dsm_impl_op(DSM_OP_DESTROY, seg->handle, 0, &seg->impl_private,
						&seg->mapped_address, &seg->mapped_size, WARNING);
			if (seg->resowner != NULL)
				ResourceOwnerForgetDSM(seg->resowner, seg);
			dlist_delete(&seg->node);
			pfree(seg);
			return NULL;
		}
		ereport(ERROR,
				(errcode(ERRCODE_INSUFFICIENT_RESOURCES),
				 errmsg("too many dynamic shared memory segments")));
	}

	/* Enter the handle into a new array slot. */
	dsm_control->item[nitems].handle = seg->handle;
	/* refcnt of 1 triggers destruction, so start at 2 */
	dsm_control->item[nitems].refcnt = 2;
	dsm_control->item[nitems].impl_private_pm_handle = NULL;
	dsm_control->item[nitems].pinned = false;
	seg->control_slot = nitems;
	dsm_control->nitems++;
	LWLockRelease(DynamicSharedMemoryControlLock);

	return seg;
}