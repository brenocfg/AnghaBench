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

/* Variables and functions */
 int /*<<< orphan*/  LOG_INFO ; 
 int /*<<< orphan*/  blog (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* malloc (size_t) ; 
 int sysctlbyname (char*,char*,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void log_processor_name(void)
{
	char   *name = NULL;
	size_t size;
	int    ret;

	ret = sysctlbyname("machdep.cpu.brand_string", NULL, &size, NULL, 0);
	if (ret != 0)
		return;

	name = malloc(size);

	ret = sysctlbyname("machdep.cpu.brand_string", name, &size, NULL, 0);
	if (ret == 0)
		blog(LOG_INFO, "CPU Name: %s", name);

	free(name);
}