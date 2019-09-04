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
struct utsname {char* machine; } ;
struct perf_env {char* arch; } ;

/* Variables and functions */
 char const* normalize_arch (char*) ; 
 scalar_t__ uname (struct utsname*) ; 

const char *perf_env__arch(struct perf_env *env)
{
	struct utsname uts;
	char *arch_name;

	if (!env || !env->arch) { /* Assume local operation */
		if (uname(&uts) < 0)
			return NULL;
		arch_name = uts.machine;
	} else
		arch_name = env->arch;

	return normalize_arch(arch_name);
}