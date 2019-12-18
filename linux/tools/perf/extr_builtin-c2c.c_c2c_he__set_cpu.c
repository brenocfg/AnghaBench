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
struct perf_sample {unsigned int cpu; } ;
struct c2c_hist_entry {int /*<<< orphan*/  cpuset; } ;

/* Variables and functions */
 scalar_t__ WARN_ONCE (int,char*) ; 
 int /*<<< orphan*/  set_bit (unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void c2c_he__set_cpu(struct c2c_hist_entry *c2c_he,
			    struct perf_sample *sample)
{
	if (WARN_ONCE(sample->cpu == (unsigned int) -1,
		      "WARNING: no sample cpu value"))
		return;

	set_bit(sample->cpu, c2c_he->cpuset);
}