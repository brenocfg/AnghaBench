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
struct perf_sample {int /*<<< orphan*/  time; int /*<<< orphan*/  tid; int /*<<< orphan*/  pid; int /*<<< orphan*/  cpu; } ;
struct intel_pt {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  INTEL_PT_ERR_LOST ; 
 int intel_pt_synth_error (struct intel_pt*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int intel_pt_lost(struct intel_pt *pt, struct perf_sample *sample)
{
	return intel_pt_synth_error(pt, INTEL_PT_ERR_LOST, sample->cpu,
				    sample->pid, sample->tid, 0, sample->time);
}