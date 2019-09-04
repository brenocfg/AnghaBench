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
struct utsname {int /*<<< orphan*/  machine; } ;
struct perf_env {int /*<<< orphan*/  arch; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  strdup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uname (struct utsname*) ; 

__attribute__((used)) static int perf_env__read_arch(struct perf_env *env)
{
	struct utsname uts;

	if (env->arch)
		return 0;

	if (!uname(&uts))
		env->arch = strdup(uts.machine);

	return env->arch ? 0 : -ENOMEM;
}