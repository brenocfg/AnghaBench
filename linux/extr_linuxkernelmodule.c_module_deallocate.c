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
struct TYPE_4__ {int /*<<< orphan*/  base; } ;
struct TYPE_3__ {int /*<<< orphan*/  base; } ;
struct module {TYPE_2__ core_layout; TYPE_1__ init_layout; } ;
struct load_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  module_arch_freeing_init (struct module*) ; 
 int /*<<< orphan*/  module_memfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  percpu_modfree (struct module*) ; 

__attribute__((used)) static void module_deallocate(struct module *mod, struct load_info *info)
{
	percpu_modfree(mod);
	module_arch_freeing_init(mod);
	module_memfree(mod->init_layout.base);
	module_memfree(mod->core_layout.base);
}