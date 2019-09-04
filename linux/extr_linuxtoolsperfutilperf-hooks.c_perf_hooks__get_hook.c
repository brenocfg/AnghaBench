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
typedef  int /*<<< orphan*/  perf_hook_func_t ;
struct TYPE_3__ {int /*<<< orphan*/ * p_hook_func; int /*<<< orphan*/  hook_name; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (TYPE_1__**) ; 
 int /*<<< orphan*/  ENOENT ; 
 int /*<<< orphan*/  ERR_PTR (int /*<<< orphan*/ ) ; 
 TYPE_1__** perf_hooks ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 

perf_hook_func_t perf_hooks__get_hook(const char *hook_name)
{
	unsigned int i;

	for (i = 0; i < ARRAY_SIZE(perf_hooks); i++) {
		if (strcmp(hook_name, perf_hooks[i]->hook_name) != 0)
			continue;

		return *(perf_hooks[i]->p_hook_func);
	}
	return ERR_PTR(-ENOENT);
}