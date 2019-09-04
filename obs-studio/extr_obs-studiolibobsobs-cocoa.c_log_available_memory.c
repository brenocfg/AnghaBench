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
typedef  int /*<<< orphan*/  memory_available ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_INFO ; 
 int /*<<< orphan*/  blog (int /*<<< orphan*/ ,char*,long long) ; 
 int sysctlbyname (char*,long long*,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void log_available_memory(void)
{
	size_t    size;
	long long memory_available;
	int       ret;

	size = sizeof(memory_available);
	ret = sysctlbyname("hw.memsize", &memory_available, &size, NULL, 0);
	if (ret == 0)
		blog(LOG_INFO, "Physical Memory: %lldMB Total",
				memory_available / 1024 / 1024);
}