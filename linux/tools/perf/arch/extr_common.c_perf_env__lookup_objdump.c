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
struct perf_env {int /*<<< orphan*/ * arch; } ;

/* Variables and functions */
 int perf_env__lookup_binutils_path (struct perf_env*,char*,char const**) ; 

int perf_env__lookup_objdump(struct perf_env *env, const char **path)
{
	/*
	 * For live mode, env->arch will be NULL and we can use
	 * the native objdump tool.
	 */
	if (env->arch == NULL)
		return 0;

	return perf_env__lookup_binutils_path(env, "objdump", path);
}