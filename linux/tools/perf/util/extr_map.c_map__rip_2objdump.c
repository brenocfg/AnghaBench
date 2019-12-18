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
typedef  scalar_t__ u64 ;
struct map {scalar_t__ reloc; scalar_t__ (* unmap_ip ) (struct map*,scalar_t__) ;TYPE_1__* dso; scalar_t__ pgoff; } ;
struct kmap {TYPE_2__* kmaps; int /*<<< orphan*/  name; } ;
struct TYPE_4__ {scalar_t__ machine; } ;
struct TYPE_3__ {scalar_t__ kernel; scalar_t__ text_offset; scalar_t__ rel; int /*<<< orphan*/  adjust_symbols; } ;

/* Variables and functions */
 scalar_t__ DSO_TYPE_USER ; 
 struct kmap* __map__kmap (struct map*) ; 
 scalar_t__ is_entry_trampoline (int /*<<< orphan*/ ) ; 
 struct map* machine__kernel_map (scalar_t__) ; 
 scalar_t__ stub1 (struct map*,scalar_t__) ; 

u64 map__rip_2objdump(struct map *map, u64 rip)
{
	struct kmap *kmap = __map__kmap(map);

	/*
	 * vmlinux does not have program headers for PTI entry trampolines and
	 * kcore may not either. However the trampoline object code is on the
	 * main kernel map, so just use that instead.
	 */
	if (kmap && is_entry_trampoline(kmap->name) && kmap->kmaps && kmap->kmaps->machine) {
		struct map *kernel_map = machine__kernel_map(kmap->kmaps->machine);

		if (kernel_map)
			map = kernel_map;
	}

	if (!map->dso->adjust_symbols)
		return rip;

	if (map->dso->rel)
		return rip - map->pgoff;

	/*
	 * kernel modules also have DSO_TYPE_USER in dso->kernel,
	 * but all kernel modules are ET_REL, so won't get here.
	 */
	if (map->dso->kernel == DSO_TYPE_USER)
		return rip + map->dso->text_offset;

	return map->unmap_ip(map, rip) - map->reloc;
}