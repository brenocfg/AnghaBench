#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ dsm_handle ;
struct TYPE_3__ {int magic; } ;
struct TYPE_4__ {int handle; scalar_t__ refcnt; int high_segment_index; scalar_t__* segment_handles; int /*<<< orphan*/  lock; TYPE_1__ segment_header; } ;
typedef  TYPE_2__ dsa_area_control ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int DSA_SEGMENT_HEADER_MAGIC ; 
 scalar_t__ DSM_HANDLE_INVALID ; 
 int /*<<< orphan*/  LWLockAcquire (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWLockRelease (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LW_EXCLUSIVE ; 
 int /*<<< orphan*/  dsm_unpin_segment (scalar_t__) ; 

void
dsa_release_in_place(void *place)
{
	dsa_area_control *control = (dsa_area_control *) place;
	int			i;

	LWLockAcquire(&control->lock, LW_EXCLUSIVE);
	Assert(control->segment_header.magic ==
		   (DSA_SEGMENT_HEADER_MAGIC ^ control->handle ^ 0));
	Assert(control->refcnt > 0);
	if (--control->refcnt == 0)
	{
		for (i = 0; i <= control->high_segment_index; ++i)
		{
			dsm_handle	handle;

			handle = control->segment_handles[i];
			if (handle != DSM_HANDLE_INVALID)
				dsm_unpin_segment(handle);
		}
	}
	LWLockRelease(&control->lock);
}