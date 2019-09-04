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
typedef  int /*<<< orphan*/  freq ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_INFO ; 
 int /*<<< orphan*/  blog (int /*<<< orphan*/ ,char*,long long) ; 
 int sysctlbyname (char*,long long*,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void log_processor_speed(void)
{
	size_t    size;
	long long freq;
	int       ret;

	size = sizeof(freq);
	ret = sysctlbyname("hw.cpufrequency", &freq, &size, NULL, 0);
	if (ret == 0)
		blog(LOG_INFO, "CPU Speed: %lldMHz", freq / 1000000);
}