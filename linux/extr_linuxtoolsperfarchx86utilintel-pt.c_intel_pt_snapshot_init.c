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
struct intel_pt_recording {int snapshot_init_done; int /*<<< orphan*/  snapshot_ref_buf_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  intel_pt_snapshot_ref_buf_size (struct intel_pt_recording*,size_t) ; 

__attribute__((used)) static int intel_pt_snapshot_init(struct intel_pt_recording *ptr,
				  size_t snapshot_buf_size)
{
	if (ptr->snapshot_init_done)
		return 0;

	ptr->snapshot_init_done = true;

	ptr->snapshot_ref_buf_size = intel_pt_snapshot_ref_buf_size(ptr,
							snapshot_buf_size);

	return 0;
}