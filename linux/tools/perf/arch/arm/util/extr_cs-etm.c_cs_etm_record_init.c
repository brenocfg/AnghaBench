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
struct auxtrace_record {int /*<<< orphan*/  read_finish; int /*<<< orphan*/  free; int /*<<< orphan*/  reference; int /*<<< orphan*/  snapshot_finish; int /*<<< orphan*/  snapshot_start; int /*<<< orphan*/  find_snapshot; int /*<<< orphan*/  info_fill; int /*<<< orphan*/  info_priv_size; int /*<<< orphan*/  recording_options; int /*<<< orphan*/  parse_snapshot_options; } ;
struct cs_etm_recording {struct auxtrace_record itr; struct perf_pmu* cs_etm_pmu; } ;

/* Variables and functions */
 int /*<<< orphan*/  CORESIGHT_ETM_PMU_NAME ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  cs_etm_find_snapshot ; 
 int /*<<< orphan*/  cs_etm_info_fill ; 
 int /*<<< orphan*/  cs_etm_info_priv_size ; 
 int /*<<< orphan*/  cs_etm_parse_snapshot_options ; 
 int /*<<< orphan*/  cs_etm_read_finish ; 
 int /*<<< orphan*/  cs_etm_recording_free ; 
 int /*<<< orphan*/  cs_etm_recording_options ; 
 int /*<<< orphan*/  cs_etm_reference ; 
 int /*<<< orphan*/  cs_etm_snapshot_finish ; 
 int /*<<< orphan*/  cs_etm_snapshot_start ; 
 struct perf_pmu* perf_pmu__find (int /*<<< orphan*/ ) ; 
 struct cs_etm_recording* zalloc (int) ; 

struct auxtrace_record *cs_etm_record_init(int *err)
{
	struct perf_pmu *cs_etm_pmu;
	struct cs_etm_recording *ptr;

	cs_etm_pmu = perf_pmu__find(CORESIGHT_ETM_PMU_NAME);

	if (!cs_etm_pmu) {
		*err = -EINVAL;
		goto out;
	}

	ptr = zalloc(sizeof(struct cs_etm_recording));
	if (!ptr) {
		*err = -ENOMEM;
		goto out;
	}

	ptr->cs_etm_pmu			= cs_etm_pmu;
	ptr->itr.parse_snapshot_options	= cs_etm_parse_snapshot_options;
	ptr->itr.recording_options	= cs_etm_recording_options;
	ptr->itr.info_priv_size		= cs_etm_info_priv_size;
	ptr->itr.info_fill		= cs_etm_info_fill;
	ptr->itr.find_snapshot		= cs_etm_find_snapshot;
	ptr->itr.snapshot_start		= cs_etm_snapshot_start;
	ptr->itr.snapshot_finish	= cs_etm_snapshot_finish;
	ptr->itr.reference		= cs_etm_reference;
	ptr->itr.free			= cs_etm_recording_free;
	ptr->itr.read_finish		= cs_etm_read_finish;

	*err = 0;
	return &ptr->itr;
out:
	return NULL;
}