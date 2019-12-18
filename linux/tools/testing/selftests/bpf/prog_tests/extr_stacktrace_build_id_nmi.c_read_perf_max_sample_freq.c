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
typedef  int __u64 ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fscanf (int /*<<< orphan*/ *,char*,int*) ; 

__attribute__((used)) static __u64 read_perf_max_sample_freq(void)
{
	__u64 sample_freq = 5000; /* fallback to 5000 on error */
	FILE *f;

	f = fopen("/proc/sys/kernel/perf_event_max_sample_rate", "r");
	if (f == NULL)
		return sample_freq;
	fscanf(f, "%llu", &sample_freq);
	fclose(f);
	return sample_freq;
}