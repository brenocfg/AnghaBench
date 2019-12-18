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
struct perf_env {int dummy; } ;
struct evsel {int dummy; } ;

/* Variables and functions */
 char const* arch_syscalls__strerrno (char const*,int) ; 
 char* perf_env__arch (struct perf_env*) ; 
 struct perf_env* perf_evsel__env (struct evsel*) ; 

__attribute__((used)) static const char *errno_to_name(struct evsel *evsel, int err)
{
	struct perf_env *env = perf_evsel__env(evsel);
	const char *arch_name = perf_env__arch(env);

	return arch_syscalls__strerrno(arch_name, err);
}