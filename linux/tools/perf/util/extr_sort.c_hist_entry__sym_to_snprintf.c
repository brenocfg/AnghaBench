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
struct hist_entry {int /*<<< orphan*/  level; TYPE_1__* branch_info; } ;
struct addr_map_symbol {int /*<<< orphan*/  addr; int /*<<< orphan*/  sym; int /*<<< orphan*/  map; } ;
struct TYPE_2__ {struct addr_map_symbol to; } ;

/* Variables and functions */
 int _hist_entry__sym_snprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,size_t,unsigned int) ; 
 int repsep_snprintf (char*,size_t,char*,unsigned int,unsigned int,char*) ; 

__attribute__((used)) static int hist_entry__sym_to_snprintf(struct hist_entry *he, char *bf,
				       size_t size, unsigned int width)
{
	if (he->branch_info) {
		struct addr_map_symbol *to = &he->branch_info->to;

		return _hist_entry__sym_snprintf(to->map, to->sym, to->addr,
						 he->level, bf, size, width);
	}

	return repsep_snprintf(bf, size, "%-*.*s", width, width, "N/A");
}