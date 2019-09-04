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
struct map {scalar_t__ (* unmap_ip ) (struct map*,int /*<<< orphan*/ ) ;scalar_t__ start; scalar_t__ end; } ;

/* Variables and functions */
 scalar_t__ stub1 (struct map*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool map__contains_symbol(struct map *map, struct symbol *sym)
{
	u64 ip = map->unmap_ip(map, sym->start);

	return ip >= map->start && ip < map->end;
}