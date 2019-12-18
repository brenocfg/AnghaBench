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
struct TYPE_4__ {int /*<<< orphan*/  text_size; int /*<<< orphan*/  base; } ;
struct TYPE_3__ {int /*<<< orphan*/  text_size; int /*<<< orphan*/  base; } ;
struct module {TYPE_2__ core_layout; TYPE_1__ init_layout; } ;

/* Variables and functions */
 struct module* __module_address (unsigned long) ; 
 int /*<<< orphan*/  within (unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

struct module *__module_text_address(unsigned long addr)
{
	struct module *mod = __module_address(addr);
	if (mod) {
		/* Make sure it's within the text section. */
		if (!within(addr, mod->init_layout.base, mod->init_layout.text_size)
		    && !within(addr, mod->core_layout.base, mod->core_layout.text_size))
			mod = NULL;
	}
	return mod;
}