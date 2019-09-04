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
struct klp_patch {TYPE_1__* mod; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int ENOSYS ; 
 int /*<<< orphan*/  is_livepatch_module (TYPE_1__*) ; 
 int /*<<< orphan*/  klp_have_reliable_stack () ; 
 int klp_init_patch (struct klp_patch*) ; 
 int /*<<< orphan*/  klp_initialized () ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 

int klp_register_patch(struct klp_patch *patch)
{
	if (!patch || !patch->mod)
		return -EINVAL;

	if (!is_livepatch_module(patch->mod)) {
		pr_err("module %s is not marked as a livepatch module\n",
		       patch->mod->name);
		return -EINVAL;
	}

	if (!klp_initialized())
		return -ENODEV;

	if (!klp_have_reliable_stack()) {
		pr_err("This architecture doesn't have support for the livepatch consistency model.\n");
		return -ENOSYS;
	}

	return klp_init_patch(patch);
}