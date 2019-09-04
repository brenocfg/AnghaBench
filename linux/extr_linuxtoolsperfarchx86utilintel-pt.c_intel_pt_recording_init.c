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
struct perf_pmu {int dummy; } ;
struct auxtrace_record {int /*<<< orphan*/  read_finish; int /*<<< orphan*/  reference; int /*<<< orphan*/  parse_snapshot_options; int /*<<< orphan*/  find_snapshot; int /*<<< orphan*/  snapshot_finish; int /*<<< orphan*/  snapshot_start; int /*<<< orphan*/  free; int /*<<< orphan*/  info_fill; int /*<<< orphan*/  info_priv_size; int /*<<< orphan*/  recording_options; } ;
struct intel_pt_recording {struct auxtrace_record itr; struct perf_pmu* intel_pt_pmu; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  INTEL_PT_PMU_NAME ; 
 int errno ; 
 int /*<<< orphan*/  intel_pt_find_snapshot ; 
 int /*<<< orphan*/  intel_pt_info_fill ; 
 int /*<<< orphan*/  intel_pt_info_priv_size ; 
 int /*<<< orphan*/  intel_pt_parse_snapshot_options ; 
 int /*<<< orphan*/  intel_pt_read_finish ; 
 int /*<<< orphan*/  intel_pt_recording_free ; 
 int /*<<< orphan*/  intel_pt_recording_options ; 
 int /*<<< orphan*/  intel_pt_reference ; 
 int /*<<< orphan*/  intel_pt_snapshot_finish ; 
 int /*<<< orphan*/  intel_pt_snapshot_start ; 
 struct perf_pmu* perf_pmu__find (int /*<<< orphan*/ ) ; 
 scalar_t__ setenv (char*,char*,int) ; 
 struct intel_pt_recording* zalloc (int) ; 

struct auxtrace_record *intel_pt_recording_init(int *err)
{
	struct perf_pmu *intel_pt_pmu = perf_pmu__find(INTEL_PT_PMU_NAME);
	struct intel_pt_recording *ptr;

	if (!intel_pt_pmu)
		return NULL;

	if (setenv("JITDUMP_USE_ARCH_TIMESTAMP", "1", 1)) {
		*err = -errno;
		return NULL;
	}

	ptr = zalloc(sizeof(struct intel_pt_recording));
	if (!ptr) {
		*err = -ENOMEM;
		return NULL;
	}

	ptr->intel_pt_pmu = intel_pt_pmu;
	ptr->itr.recording_options = intel_pt_recording_options;
	ptr->itr.info_priv_size = intel_pt_info_priv_size;
	ptr->itr.info_fill = intel_pt_info_fill;
	ptr->itr.free = intel_pt_recording_free;
	ptr->itr.snapshot_start = intel_pt_snapshot_start;
	ptr->itr.snapshot_finish = intel_pt_snapshot_finish;
	ptr->itr.find_snapshot = intel_pt_find_snapshot;
	ptr->itr.parse_snapshot_options = intel_pt_parse_snapshot_options;
	ptr->itr.reference = intel_pt_reference;
	ptr->itr.read_finish = intel_pt_read_finish;
	return &ptr->itr;
}