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
typedef  int /*<<< orphan*/  kernel_version ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_INFO ; 
 int /*<<< orphan*/  blog (int /*<<< orphan*/ ,char*,char*) ; 
 int sysctlbyname (char*,char*,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void log_kernel_version(void)
{
	char   kernel_version[1024];
	size_t size = sizeof(kernel_version);
	int    ret;

	ret = sysctlbyname("kern.osrelease", kernel_version, &size,
			NULL, 0);
	if (ret == 0)
		blog(LOG_INFO, "Kernel Version: %s", kernel_version);
}