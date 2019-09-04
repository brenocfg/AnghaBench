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
typedef  scalar_t__ u64 ;
struct symbol {int /*<<< orphan*/  start; } ;
struct ref_reloc_sym {scalar_t__ unrelocated_addr; scalar_t__ addr; int /*<<< orphan*/  name; } ;
struct map {int /*<<< orphan*/  start; scalar_t__ reloc; scalar_t__ (* unmap_ip ) (struct map*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  host_machine ; 
 struct ref_reloc_sym* kernel_get_ref_reloc_sym () ; 
 struct symbol* machine__find_kernel_symbol_by_name (int /*<<< orphan*/ ,char const*,struct map**) ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (struct map*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int kernel_get_symbol_address_by_name(const char *name, u64 *addr,
					     bool reloc, bool reladdr)
{
	struct ref_reloc_sym *reloc_sym;
	struct symbol *sym;
	struct map *map;

	/* ref_reloc_sym is just a label. Need a special fix*/
	reloc_sym = kernel_get_ref_reloc_sym();
	if (reloc_sym && strcmp(name, reloc_sym->name) == 0)
		*addr = (reloc) ? reloc_sym->addr : reloc_sym->unrelocated_addr;
	else {
		sym = machine__find_kernel_symbol_by_name(host_machine, name, &map);
		if (!sym)
			return -ENOENT;
		*addr = map->unmap_ip(map, sym->start) -
			((reloc) ? 0 : map->reloc) -
			((reladdr) ? map->start : 0);
	}
	return 0;
}