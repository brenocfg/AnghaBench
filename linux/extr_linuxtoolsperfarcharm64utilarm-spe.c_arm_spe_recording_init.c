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
struct auxtrace_record {scalar_t__ alignment; int /*<<< orphan*/  read_finish; int /*<<< orphan*/  reference; int /*<<< orphan*/  free; int /*<<< orphan*/  info_fill; int /*<<< orphan*/  info_priv_size; int /*<<< orphan*/  recording_options; } ;
struct arm_spe_recording {struct auxtrace_record itr; struct perf_pmu* arm_spe_pmu; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  arm_spe_info_fill ; 
 int /*<<< orphan*/  arm_spe_info_priv_size ; 
 int /*<<< orphan*/  arm_spe_read_finish ; 
 int /*<<< orphan*/  arm_spe_recording_free ; 
 int /*<<< orphan*/  arm_spe_recording_options ; 
 int /*<<< orphan*/  arm_spe_reference ; 
 struct arm_spe_recording* zalloc (int) ; 

struct auxtrace_record *arm_spe_recording_init(int *err,
					       struct perf_pmu *arm_spe_pmu)
{
	struct arm_spe_recording *sper;

	if (!arm_spe_pmu) {
		*err = -ENODEV;
		return NULL;
	}

	sper = zalloc(sizeof(struct arm_spe_recording));
	if (!sper) {
		*err = -ENOMEM;
		return NULL;
	}

	sper->arm_spe_pmu = arm_spe_pmu;
	sper->itr.recording_options = arm_spe_recording_options;
	sper->itr.info_priv_size = arm_spe_info_priv_size;
	sper->itr.info_fill = arm_spe_info_fill;
	sper->itr.free = arm_spe_recording_free;
	sper->itr.reference = arm_spe_reference;
	sper->itr.read_finish = arm_spe_read_finish;
	sper->itr.alignment = 0;

	*err = 0;
	return &sper->itr;
}