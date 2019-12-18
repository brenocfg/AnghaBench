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
 int sscanf (char const*,char*,int*) ; 

__attribute__((used)) static int s390_cpumsf_get_type(const char *cpuid)
{
	int ret, family = 0;

	ret = sscanf(cpuid, "%*[^,],%u", &family);
	return (ret == 1) ? family : 0;
}