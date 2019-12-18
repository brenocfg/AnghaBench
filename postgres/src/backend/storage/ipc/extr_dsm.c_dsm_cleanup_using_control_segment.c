#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32 ;
typedef  int /*<<< orphan*/  dsm_handle ;
struct TYPE_5__ {size_t nitems; TYPE_1__* item; } ;
typedef  TYPE_2__ dsm_control_header ;
struct TYPE_4__ {size_t refcnt; int /*<<< orphan*/  handle; } ;
typedef  int /*<<< orphan*/  Size ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG1 ; 
 int /*<<< orphan*/  DEBUG2 ; 
 int /*<<< orphan*/  DSM_OP_ATTACH ; 
 int /*<<< orphan*/  DSM_OP_DESTROY ; 
 int /*<<< orphan*/  DSM_OP_DETACH ; 
 int /*<<< orphan*/  LOG ; 
 int /*<<< orphan*/  dsm_control_segment_sane (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsm_impl_op (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void**,void**,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 

void
dsm_cleanup_using_control_segment(dsm_handle old_control_handle)
{
	void	   *mapped_address = NULL;
	void	   *junk_mapped_address = NULL;
	void	   *impl_private = NULL;
	void	   *junk_impl_private = NULL;
	Size		mapped_size = 0;
	Size		junk_mapped_size = 0;
	uint32		nitems;
	uint32		i;
	dsm_control_header *old_control;

	/*
	 * Try to attach the segment.  If this fails, it probably just means that
	 * the operating system has been rebooted and the segment no longer
	 * exists, or an unrelated process has used the same shm ID.  So just fall
	 * out quietly.
	 */
	if (!dsm_impl_op(DSM_OP_ATTACH, old_control_handle, 0, &impl_private,
					 &mapped_address, &mapped_size, DEBUG1))
		return;

	/*
	 * We've managed to reattach it, but the contents might not be sane. If
	 * they aren't, we disregard the segment after all.
	 */
	old_control = (dsm_control_header *) mapped_address;
	if (!dsm_control_segment_sane(old_control, mapped_size))
	{
		dsm_impl_op(DSM_OP_DETACH, old_control_handle, 0, &impl_private,
					&mapped_address, &mapped_size, LOG);
		return;
	}

	/*
	 * OK, the control segment looks basically valid, so we can use it to get
	 * a list of segments that need to be removed.
	 */
	nitems = old_control->nitems;
	for (i = 0; i < nitems; ++i)
	{
		dsm_handle	handle;
		uint32		refcnt;

		/* If the reference count is 0, the slot is actually unused. */
		refcnt = old_control->item[i].refcnt;
		if (refcnt == 0)
			continue;

		/* Log debugging information. */
		handle = old_control->item[i].handle;
		elog(DEBUG2, "cleaning up orphaned dynamic shared memory with ID %u (reference count %u)",
			 handle, refcnt);

		/* Destroy the referenced segment. */
		dsm_impl_op(DSM_OP_DESTROY, handle, 0, &junk_impl_private,
					&junk_mapped_address, &junk_mapped_size, LOG);
	}

	/* Destroy the old control segment, too. */
	elog(DEBUG2,
		 "cleaning up dynamic shared memory control segment with ID %u",
		 old_control_handle);
	dsm_impl_op(DSM_OP_DESTROY, old_control_handle, 0, &impl_private,
				&mapped_address, &mapped_size, LOG);
}