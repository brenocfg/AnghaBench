#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ perf_hook_func_t ;
struct TYPE_3__ {void* hook_ctx; scalar_t__* p_hook_func; int /*<<< orphan*/  hook_name; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (TYPE_1__**) ; 
 int ENOENT ; 
 TYPE_1__** perf_hooks ; 
 int /*<<< orphan*/  pr_warning (char*,char const*) ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 

int perf_hooks__set_hook(const char *hook_name,
			 perf_hook_func_t hook_func,
			 void *hook_ctx)
{
	unsigned int i;

	for (i = 0; i < ARRAY_SIZE(perf_hooks); i++) {
		if (strcmp(hook_name, perf_hooks[i]->hook_name) != 0)
			continue;

		if (*(perf_hooks[i]->p_hook_func))
			pr_warning("Overwrite existing hook: %s\n", hook_name);
		*(perf_hooks[i]->p_hook_func) = hook_func;
		perf_hooks[i]->hook_ctx = hook_ctx;
		return 0;
	}
	return -ENOENT;
}