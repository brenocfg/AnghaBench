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
struct addr_map_symbol {int /*<<< orphan*/  sym; int /*<<< orphan*/  al_addr; int /*<<< orphan*/  map; } ;

/* Variables and functions */
 char* map__srcline (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static char *addr_map_symbol__srcline(struct addr_map_symbol *ams)
{
	return map__srcline(ams->map, ams->al_addr, ams->sym);
}