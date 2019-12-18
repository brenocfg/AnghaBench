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
struct klp_object {TYPE_1__* mod; } ;
struct TYPE_2__ {size_t state; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/ * module_state ; 
 int /*<<< orphan*/  pr_info (char*,char const*,...) ; 

__attribute__((used)) static void callback_info(const char *callback, struct klp_object *obj)
{
	if (obj->mod)
		pr_info("%s: %s -> %s\n", callback, obj->mod->name,
			module_state[obj->mod->state]);
	else
		pr_info("%s: vmlinux\n", callback);
}