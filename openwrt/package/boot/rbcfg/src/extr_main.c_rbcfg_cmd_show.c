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
struct rbcfg_env {char* name; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct rbcfg_env*) ; 
 int RB_ERR_INVALID ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,char const*) ; 
 char* rbcfg_env_get (struct rbcfg_env const*) ; 
 struct rbcfg_env* rbcfg_envs ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  usage () ; 

__attribute__((used)) static int
rbcfg_cmd_show(int argc, const char *argv[])
{
	int i;

	if (argc != 0) {
		usage();
		return RB_ERR_INVALID;
	}

	for (i = 0; i < ARRAY_SIZE(rbcfg_envs); i++) {
		const struct rbcfg_env *env = &rbcfg_envs[i];
		const char *value;

		value = rbcfg_env_get(env);
		if (value)
			fprintf(stdout, "%s=%s\n", env->name, value);
	}

	return 0;
}