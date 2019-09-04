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
struct symbol {char* name; int /*<<< orphan*/  start; } ;
struct map {unsigned long long (* unmap_ip ) (struct map*,int /*<<< orphan*/ ) ;TYPE_1__* dso; } ;
struct machine {int dummy; } ;
struct TYPE_2__ {scalar_t__ short_name; } ;

/* Variables and functions */
 scalar_t__ __map__is_kmodule (struct map*) ; 
 struct symbol* machine__find_kernel_symbol (struct machine*,unsigned long long,struct map**) ; 
 unsigned long long stub1 (struct map*,int /*<<< orphan*/ ) ; 

char *machine__resolve_kernel_addr(void *vmachine, unsigned long long *addrp, char **modp)
{
	struct machine *machine = vmachine;
	struct map *map;
	struct symbol *sym = machine__find_kernel_symbol(machine, *addrp, &map);

	if (sym == NULL)
		return NULL;

	*modp = __map__is_kmodule(map) ? (char *)map->dso->short_name : NULL;
	*addrp = map->unmap_ip(map, sym->start);
	return sym->name;
}