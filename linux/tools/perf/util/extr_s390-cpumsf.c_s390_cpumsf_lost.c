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
struct s390_cpumsf {int dummy; } ;
struct perf_sample {int /*<<< orphan*/  time; int /*<<< orphan*/  tid; int /*<<< orphan*/  pid; int /*<<< orphan*/  cpu; } ;

/* Variables and functions */
 int s390_cpumsf_synth_error (struct s390_cpumsf*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int s390_cpumsf_lost(struct s390_cpumsf *sf, struct perf_sample *sample)
{
	return s390_cpumsf_synth_error(sf, 1, sample->cpu,
				       sample->pid, sample->tid, 0,
				       sample->time);
}