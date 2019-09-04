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
struct perf_sample {int /*<<< orphan*/  time; } ;

/* Variables and functions */
 scalar_t__ perf_time__skip_sample (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ptime ; 

__attribute__((used)) static bool perf_kmem__skip_sample(struct perf_sample *sample)
{
	/* skip sample based on time? */
	if (perf_time__skip_sample(&ptime, sample->time))
		return true;

	return false;
}