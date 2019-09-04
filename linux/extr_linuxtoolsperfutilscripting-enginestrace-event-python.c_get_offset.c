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
struct symbol {scalar_t__ end; unsigned long start; } ;
struct addr_location {scalar_t__ addr; TYPE_1__* map; } ;
struct TYPE_2__ {unsigned long start; } ;

/* Variables and functions */

__attribute__((used)) static unsigned long get_offset(struct symbol *sym, struct addr_location *al)
{
	unsigned long offset;

	if (al->addr < sym->end)
		offset = al->addr - sym->start;
	else
		offset = al->addr - al->map->start - sym->start;

	return offset;
}