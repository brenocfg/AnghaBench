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
struct rbcfg_value {int /*<<< orphan*/  name; } ;
struct rbcfg_env {unsigned int num_values; struct rbcfg_value* values; } ;

/* Variables and functions */
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static const struct rbcfg_value *
rbcfg_env_find(const struct rbcfg_env *env, const char *name)
{
	unsigned i;

	for (i = 0; i < env->num_values; i++) {
		const struct rbcfg_value *v = &env->values[i];

		if (strcmp(v->name, name) == 0)
			return v;
	}

	return NULL;
}