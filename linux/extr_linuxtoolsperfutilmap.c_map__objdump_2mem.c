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
typedef  scalar_t__ u64 ;
struct map {scalar_t__ reloc; TYPE_1__* dso; scalar_t__ (* unmap_ip ) (struct map*,scalar_t__) ;scalar_t__ pgoff; } ;
struct TYPE_2__ {scalar_t__ kernel; scalar_t__ text_offset; scalar_t__ rel; int /*<<< orphan*/  adjust_symbols; } ;

/* Variables and functions */
 scalar_t__ DSO_TYPE_USER ; 
 scalar_t__ stub1 (struct map*,scalar_t__) ; 
 scalar_t__ stub2 (struct map*,scalar_t__) ; 
 scalar_t__ stub3 (struct map*,scalar_t__) ; 

u64 map__objdump_2mem(struct map *map, u64 ip)
{
	if (!map->dso->adjust_symbols)
		return map->unmap_ip(map, ip);

	if (map->dso->rel)
		return map->unmap_ip(map, ip + map->pgoff);

	/*
	 * kernel modules also have DSO_TYPE_USER in dso->kernel,
	 * but all kernel modules are ET_REL, so won't get here.
	 */
	if (map->dso->kernel == DSO_TYPE_USER)
		return map->unmap_ip(map, ip - map->dso->text_offset);

	return ip + map->reloc;
}