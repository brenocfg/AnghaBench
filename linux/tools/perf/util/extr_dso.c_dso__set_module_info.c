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
struct machine {int dummy; } ;
struct kmod_path {int /*<<< orphan*/  name; scalar_t__ comp; scalar_t__ kmod; } ;
struct dso {scalar_t__ comp; int /*<<< orphan*/  symtab_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSO_BINARY_TYPE__GUEST_KMODULE ; 
 int /*<<< orphan*/  DSO_BINARY_TYPE__SYSTEM_PATH_KMODULE ; 
 int /*<<< orphan*/  dso__set_short_name (struct dso*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ machine__is_host (struct machine*) ; 
 int /*<<< orphan*/  strdup (int /*<<< orphan*/ ) ; 

void dso__set_module_info(struct dso *dso, struct kmod_path *m,
			  struct machine *machine)
{
	if (machine__is_host(machine))
		dso->symtab_type = DSO_BINARY_TYPE__SYSTEM_PATH_KMODULE;
	else
		dso->symtab_type = DSO_BINARY_TYPE__GUEST_KMODULE;

	/* _KMODULE_COMP should be next to _KMODULE */
	if (m->kmod && m->comp) {
		dso->symtab_type++;
		dso->comp = m->comp;
	}

	dso__set_short_name(dso, strdup(m->name), true);
}