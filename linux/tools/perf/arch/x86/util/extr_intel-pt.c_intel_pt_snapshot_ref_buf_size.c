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
struct intel_pt_recording {int snapshot_size; int /*<<< orphan*/  evlist; int /*<<< orphan*/  intel_pt_pmu; } ;

/* Variables and functions */
 size_t intel_pt_psb_period (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static size_t intel_pt_snapshot_ref_buf_size(struct intel_pt_recording *ptr,
					     size_t snapshot_buf_size)
{
	const size_t max_size = 256 * 1024;
	size_t buf_size = 0, psb_period;

	if (ptr->snapshot_size <= 64 * 1024)
		return 0;

	psb_period = intel_pt_psb_period(ptr->intel_pt_pmu, ptr->evlist);
	if (psb_period)
		buf_size = psb_period * 2;

	if (!buf_size || buf_size > max_size)
		buf_size = max_size;

	if (buf_size >= snapshot_buf_size)
		return 0;

	if (buf_size >= ptr->snapshot_size / 2)
		return 0;

	return buf_size;
}