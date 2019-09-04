#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ size; int /*<<< orphan*/  base; } ;
struct TYPE_3__ {scalar_t__ size; int /*<<< orphan*/  base; } ;
struct module {TYPE_2__ init_layout; TYPE_1__ core_layout; } ;

/* Variables and functions */
 int /*<<< orphan*/  __mod_update_bounds (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void mod_update_bounds(struct module *mod)
{
	__mod_update_bounds(mod->core_layout.base, mod->core_layout.size);
	if (mod->init_layout.size)
		__mod_update_bounds(mod->init_layout.base, mod->init_layout.size);
}