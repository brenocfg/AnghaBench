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
struct auxtrace_record {int alignment; int /*<<< orphan*/  read_finish; int /*<<< orphan*/  reference; int /*<<< orphan*/  parse_snapshot_options; int /*<<< orphan*/  find_snapshot; int /*<<< orphan*/  snapshot_finish; int /*<<< orphan*/  snapshot_start; int /*<<< orphan*/  free; int /*<<< orphan*/  info_fill; int /*<<< orphan*/  info_priv_size; int /*<<< orphan*/  recording_options; } ;
struct intel_bts_recording {struct auxtrace_record itr; struct perf_pmu* intel_bts_pmu; } ;
struct branch {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  INTEL_BTS_PMU_NAME ; 
 int errno ; 
 int /*<<< orphan*/  intel_bts_find_snapshot ; 
 int /*<<< orphan*/  intel_bts_info_fill ; 
 int /*<<< orphan*/  intel_bts_info_priv_size ; 
 int /*<<< orphan*/  intel_bts_parse_snapshot_options ; 
 int /*<<< orphan*/  intel_bts_read_finish ; 
 int /*<<< orphan*/  intel_bts_recording_free ; 
 int /*<<< orphan*/  intel_bts_recording_options ; 
 int /*<<< orphan*/  intel_bts_reference ; 
 int /*<<< orphan*/  intel_bts_snapshot_finish ; 
 int /*<<< orphan*/  intel_bts_snapshot_start ; 
 struct perf_pmu* perf_pmu__find (int /*<<< orphan*/ ) ; 
 scalar_t__ setenv (char*,char*,int) ; 
 struct intel_bts_recording* zalloc (int) ; 

struct auxtrace_record *intel_bts_recording_init(int *err)
{
	struct perf_pmu *intel_bts_pmu = perf_pmu__find(INTEL_BTS_PMU_NAME);
	struct intel_bts_recording *btsr;

	if (!intel_bts_pmu)
		return NULL;

	if (setenv("JITDUMP_USE_ARCH_TIMESTAMP", "1", 1)) {
		*err = -errno;
		return NULL;
	}

	btsr = zalloc(sizeof(struct intel_bts_recording));
	if (!btsr) {
		*err = -ENOMEM;
		return NULL;
	}

	btsr->intel_bts_pmu = intel_bts_pmu;
	btsr->itr.recording_options = intel_bts_recording_options;
	btsr->itr.info_priv_size = intel_bts_info_priv_size;
	btsr->itr.info_fill = intel_bts_info_fill;
	btsr->itr.free = intel_bts_recording_free;
	btsr->itr.snapshot_start = intel_bts_snapshot_start;
	btsr->itr.snapshot_finish = intel_bts_snapshot_finish;
	btsr->itr.find_snapshot = intel_bts_find_snapshot;
	btsr->itr.parse_snapshot_options = intel_bts_parse_snapshot_options;
	btsr->itr.reference = intel_bts_reference;
	btsr->itr.read_finish = intel_bts_read_finish;
	btsr->itr.alignment = sizeof(struct branch);
	return &btsr->itr;
}