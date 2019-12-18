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
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  DSM_OP_ATTACH ; 
 int /*<<< orphan*/  DSM_OP_DETACH ; 
 int /*<<< orphan*/  ERRCODE_INTERNAL_ERROR ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  FATAL ; 
 int /*<<< orphan*/  WARNING ; 
 void* dsm_control ; 
 scalar_t__ dsm_control_handle ; 
 int /*<<< orphan*/  dsm_control_impl_private ; 
 int /*<<< orphan*/  dsm_control_mapped_size ; 
 int /*<<< orphan*/  dsm_control_segment_sane (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsm_impl_op (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int dsm_init_done ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*) ; 

__attribute__((used)) static void
dsm_backend_startup(void)
{
#ifdef EXEC_BACKEND
	{
		void	   *control_address = NULL;

		/* Attach control segment. */
		Assert(dsm_control_handle != 0);
		dsm_impl_op(DSM_OP_ATTACH, dsm_control_handle, 0,
					&dsm_control_impl_private, &control_address,
					&dsm_control_mapped_size, ERROR);
		dsm_control = control_address;
		/* If control segment doesn't look sane, something is badly wrong. */
		if (!dsm_control_segment_sane(dsm_control, dsm_control_mapped_size))
		{
			dsm_impl_op(DSM_OP_DETACH, dsm_control_handle, 0,
						&dsm_control_impl_private, &control_address,
						&dsm_control_mapped_size, WARNING);
			ereport(FATAL,
					(errcode(ERRCODE_INTERNAL_ERROR),
					 errmsg("dynamic shared memory control segment is not valid")));
		}
	}
#endif

	dsm_init_done = true;
}