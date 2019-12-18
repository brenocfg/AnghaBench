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

/* Variables and functions */
 int /*<<< orphan*/  DSM_OP_DETACH ; 
 int /*<<< orphan*/  ERROR ; 
 int dlist_head_element (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dlist_is_empty (int /*<<< orphan*/ *) ; 
 void* dsm_control ; 
 int /*<<< orphan*/  dsm_control_handle ; 
 int /*<<< orphan*/  dsm_control_impl_private ; 
 int /*<<< orphan*/  dsm_control_mapped_size ; 
 int /*<<< orphan*/  dsm_detach (int) ; 
 int /*<<< orphan*/  dsm_impl_op (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int dsm_segment ; 
 int /*<<< orphan*/  dsm_segment_list ; 
 int /*<<< orphan*/  node ; 
 int seg ; 

void
dsm_detach_all(void)
{
	void	   *control_address = dsm_control;

	while (!dlist_is_empty(&dsm_segment_list))
	{
		dsm_segment *seg;

		seg = dlist_head_element(dsm_segment, node, &dsm_segment_list);
		dsm_detach(seg);
	}

	if (control_address != NULL)
		dsm_impl_op(DSM_OP_DETACH, dsm_control_handle, 0,
					&dsm_control_impl_private, &control_address,
					&dsm_control_mapped_size, ERROR);
}