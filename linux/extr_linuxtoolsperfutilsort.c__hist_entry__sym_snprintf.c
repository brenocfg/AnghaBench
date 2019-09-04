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
struct symbol {scalar_t__ type; scalar_t__ inlined; scalar_t__ name; int /*<<< orphan*/  start; } ;
struct map {scalar_t__ (* unmap_ip ) (struct map*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  dso; } ;

/* Variables and functions */
 int BITS_PER_LONG ; 
 scalar_t__ STT_OBJECT ; 
 char dso__symtab_origin (int /*<<< orphan*/ ) ; 
 scalar_t__ repsep_snprintf (char*,size_t,char*,...) ; 
 scalar_t__ stub1 (struct map*,int /*<<< orphan*/ ) ; 
 scalar_t__ verbose ; 

__attribute__((used)) static int _hist_entry__sym_snprintf(struct map *map, struct symbol *sym,
				     u64 ip, char level, char *bf, size_t size,
				     unsigned int width)
{
	size_t ret = 0;

	if (verbose > 0) {
		char o = map ? dso__symtab_origin(map->dso) : '!';
		ret += repsep_snprintf(bf, size, "%-#*llx %c ",
				       BITS_PER_LONG / 4 + 2, ip, o);
	}

	ret += repsep_snprintf(bf + ret, size - ret, "[%c] ", level);
	if (sym && map) {
		if (sym->type == STT_OBJECT) {
			ret += repsep_snprintf(bf + ret, size - ret, "%s", sym->name);
			ret += repsep_snprintf(bf + ret, size - ret, "+0x%llx",
					ip - map->unmap_ip(map, sym->start));
		} else {
			ret += repsep_snprintf(bf + ret, size - ret, "%.*s",
					       width - ret,
					       sym->name);
			if (sym->inlined)
				ret += repsep_snprintf(bf + ret, size - ret,
						       " (inlined)");
		}
	} else {
		size_t len = BITS_PER_LONG / 4;
		ret += repsep_snprintf(bf + ret, size - ret, "%-#.*llx",
				       len, ip);
	}

	return ret;
}