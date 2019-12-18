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
typedef  int /*<<< orphan*/  uint64_t ;
struct symbol {int dummy; } ;
struct map {int dummy; } ;
struct hist_entry {int /*<<< orphan*/  level; TYPE_1__* mem_info; } ;
struct TYPE_4__ {struct symbol* sym; struct map* map; int /*<<< orphan*/  addr; } ;
struct TYPE_3__ {TYPE_2__ daddr; } ;

/* Variables and functions */
 int _hist_entry__sym_snprintf (struct map*,struct symbol*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,size_t,unsigned int) ; 

__attribute__((used)) static int hist_entry__daddr_snprintf(struct hist_entry *he, char *bf,
				    size_t size, unsigned int width)
{
	uint64_t addr = 0;
	struct map *map = NULL;
	struct symbol *sym = NULL;

	if (he->mem_info) {
		addr = he->mem_info->daddr.addr;
		map = he->mem_info->daddr.map;
		sym = he->mem_info->daddr.sym;
	}
	return _hist_entry__sym_snprintf(map, sym, addr, he->level, bf, size,
					 width);
}