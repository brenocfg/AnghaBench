#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct utsname {char* release; } ;
struct perf_env {char* os_release; } ;
typedef  int /*<<< orphan*/  bf ;
struct TYPE_2__ {scalar_t__* symfs; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (char**) ; 
 int PATH_MAX ; 
 int /*<<< orphan*/ * malloc (int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 
 TYPE_1__ symbol_conf ; 
 scalar_t__ uname (struct utsname*) ; 
 int /*<<< orphan*/ * vmlinux_path ; 
 scalar_t__ vmlinux_path__add (char*) ; 
 int /*<<< orphan*/  vmlinux_path__exit () ; 
 char** vmlinux_paths ; 
 char** vmlinux_paths_upd ; 

__attribute__((used)) static int vmlinux_path__init(struct perf_env *env)
{
	struct utsname uts;
	char bf[PATH_MAX];
	char *kernel_version;
	unsigned int i;

	vmlinux_path = malloc(sizeof(char *) * (ARRAY_SIZE(vmlinux_paths) +
			      ARRAY_SIZE(vmlinux_paths_upd)));
	if (vmlinux_path == NULL)
		return -1;

	for (i = 0; i < ARRAY_SIZE(vmlinux_paths); i++)
		if (vmlinux_path__add(vmlinux_paths[i]) < 0)
			goto out_fail;

	/* only try kernel version if no symfs was given */
	if (symbol_conf.symfs[0] != 0)
		return 0;

	if (env) {
		kernel_version = env->os_release;
	} else {
		if (uname(&uts) < 0)
			goto out_fail;

		kernel_version = uts.release;
	}

	for (i = 0; i < ARRAY_SIZE(vmlinux_paths_upd); i++) {
		snprintf(bf, sizeof(bf), vmlinux_paths_upd[i], kernel_version);
		if (vmlinux_path__add(bf) < 0)
			goto out_fail;
	}

	return 0;

out_fail:
	vmlinux_path__exit();
	return -1;
}