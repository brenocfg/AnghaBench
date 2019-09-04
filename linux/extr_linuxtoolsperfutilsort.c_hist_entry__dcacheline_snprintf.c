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
struct map {int prot; int flags; scalar_t__ ino_generation; scalar_t__ ino; scalar_t__ min; scalar_t__ maj; } ;
struct hist_entry {char level; scalar_t__ cpumode; TYPE_2__* mem_info; } ;
struct TYPE_3__ {struct symbol* sym; struct map* map; int /*<<< orphan*/  al_addr; } ;
struct TYPE_4__ {TYPE_1__ daddr; } ;

/* Variables and functions */
 int MAP_SHARED ; 
 scalar_t__ PERF_RECORD_MISC_KERNEL ; 
 int PROT_EXEC ; 
 int _hist_entry__sym_snprintf (struct map*,struct symbol*,int /*<<< orphan*/ ,char,char*,size_t,unsigned int) ; 
 int /*<<< orphan*/  cl_address (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hist_entry__dcacheline_snprintf(struct hist_entry *he, char *bf,
					  size_t size, unsigned int width)
{

	uint64_t addr = 0;
	struct map *map = NULL;
	struct symbol *sym = NULL;
	char level = he->level;

	if (he->mem_info) {
		addr = cl_address(he->mem_info->daddr.al_addr);
		map = he->mem_info->daddr.map;
		sym = he->mem_info->daddr.sym;

		/* print [s] for shared data mmaps */
		if ((he->cpumode != PERF_RECORD_MISC_KERNEL) &&
		     map && !(map->prot & PROT_EXEC) &&
		    (map->flags & MAP_SHARED) &&
		    (map->maj || map->min || map->ino ||
		     map->ino_generation))
			level = 's';
		else if (!map)
			level = 'X';
	}
	return _hist_entry__sym_snprintf(map, sym, addr, level, bf, size,
					 width);
}