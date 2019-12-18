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
typedef  int /*<<< orphan*/  u64 ;
struct intel_pt_snapshot_ref {int /*<<< orphan*/  ref_buf; int /*<<< orphan*/  ref_offset; } ;
struct intel_pt_recording {int /*<<< orphan*/  snapshot_ref_buf_size; struct intel_pt_snapshot_ref* snapshot_refs; } ;
struct auxtrace_mmap {int /*<<< orphan*/  len; } ;

/* Variables and functions */
 int intel_pt_compare_ref (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_pt_copy_ref (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool intel_pt_wrapped(struct intel_pt_recording *ptr, int idx,
			     struct auxtrace_mmap *mm, unsigned char *data,
			     u64 head)
{
	struct intel_pt_snapshot_ref *ref = &ptr->snapshot_refs[idx];
	bool wrapped;

	wrapped = intel_pt_compare_ref(ref->ref_buf, ref->ref_offset,
				       ptr->snapshot_ref_buf_size, mm->len,
				       data, head);

	intel_pt_copy_ref(ref->ref_buf, ptr->snapshot_ref_buf_size, mm->len,
			  data, head);

	return wrapped;
}