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
struct perf_env {char const** cmdline_argv; int nr_cmdline; } ;

/* Variables and functions */
 int ENOMEM ; 
 char const** calloc (int,int) ; 
 int /*<<< orphan*/  zfree (char const***) ; 

int perf_env__set_cmdline(struct perf_env *env, int argc, const char *argv[])
{
	int i;

	/* do not include NULL termination */
	env->cmdline_argv = calloc(argc, sizeof(char *));
	if (env->cmdline_argv == NULL)
		goto out_enomem;

	/*
	 * Must copy argv contents because it gets moved around during option
	 * parsing:
	 */
	for (i = 0; i < argc ; i++) {
		env->cmdline_argv[i] = argv[i];
		if (env->cmdline_argv[i] == NULL)
			goto out_free;
	}

	env->nr_cmdline = argc;

	return 0;
out_free:
	zfree(&env->cmdline_argv);
out_enomem:
	return -ENOMEM;
}