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
struct intel_pt_recording {size_t snapshot_ref_buf_size; TYPE_1__* snapshot_refs; } ;
struct TYPE_2__ {size_t ref_offset; void* ref_buf; } ;

/* Variables and functions */
 int ENOMEM ; 
 void* zalloc (size_t) ; 

__attribute__((used)) static int intel_pt_alloc_snapshot_ref(struct intel_pt_recording *ptr, int idx,
				       size_t snapshot_buf_size)
{
	size_t ref_buf_size = ptr->snapshot_ref_buf_size;
	void *ref_buf;

	ref_buf = zalloc(ref_buf_size);
	if (!ref_buf)
		return -ENOMEM;

	ptr->snapshot_refs[idx].ref_buf = ref_buf;
	ptr->snapshot_refs[idx].ref_offset = snapshot_buf_size - ref_buf_size;

	return 0;
}