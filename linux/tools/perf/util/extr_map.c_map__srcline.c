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
typedef  int /*<<< orphan*/  u64 ;
struct symbol {int dummy; } ;
struct map {int /*<<< orphan*/  dso; } ;

/* Variables and functions */
 char* SRCLINE_UNKNOWN ; 
 char* get_srcline (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct symbol*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  map__rip_2objdump (struct map*,int /*<<< orphan*/ ) ; 

char *map__srcline(struct map *map, u64 addr, struct symbol *sym)
{
	if (map == NULL)
		return SRCLINE_UNKNOWN;
	return get_srcline(map->dso, map__rip_2objdump(map, addr), sym, true, true, addr);
}