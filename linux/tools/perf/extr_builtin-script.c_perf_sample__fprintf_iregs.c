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
struct perf_sample {int /*<<< orphan*/  intr_regs; } ;
struct perf_event_attr {int /*<<< orphan*/  sample_regs_intr; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int perf_sample__fprintf_regs (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int perf_sample__fprintf_iregs(struct perf_sample *sample,
				      struct perf_event_attr *attr, FILE *fp)
{
	return perf_sample__fprintf_regs(&sample->intr_regs,
					 attr->sample_regs_intr, fp);
}