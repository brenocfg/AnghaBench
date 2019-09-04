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
struct map_symbol {struct map* map; } ;
struct map {int /*<<< orphan*/  (* map_ip ) (struct map*,int /*<<< orphan*/ ) ;} ;
struct TYPE_4__ {scalar_t__ addr; int /*<<< orphan*/  sym; int /*<<< orphan*/ * name; } ;
struct ins_operands {char* raw; TYPE_2__ target; } ;
struct TYPE_3__ {char skip_functions_char; } ;
struct arch {TYPE_1__ objdump; } ;
struct addr_map_symbol {int /*<<< orphan*/  sym; int /*<<< orphan*/  addr; struct map* map; } ;

/* Variables and functions */
 int /*<<< orphan*/  map__objdump_2mem (struct map*,scalar_t__) ; 
 scalar_t__ map__rip_2objdump (struct map*,int /*<<< orphan*/ ) ; 
 scalar_t__ map_groups__find_ams (struct addr_map_symbol*) ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/ * strdup (char*) ; 
 int /*<<< orphan*/ * strstr (char*,char*) ; 
 void* strtoull (char*,char**,int) ; 
 int /*<<< orphan*/  stub1 (struct map*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int call__parse(struct arch *arch, struct ins_operands *ops, struct map_symbol *ms)
{
	char *endptr, *tok, *name;
	struct map *map = ms->map;
	struct addr_map_symbol target = {
		.map = map,
	};

	ops->target.addr = strtoull(ops->raw, &endptr, 16);

	name = strchr(endptr, '<');
	if (name == NULL)
		goto indirect_call;

	name++;

	if (arch->objdump.skip_functions_char &&
	    strchr(name, arch->objdump.skip_functions_char))
		return -1;

	tok = strchr(name, '>');
	if (tok == NULL)
		return -1;

	*tok = '\0';
	ops->target.name = strdup(name);
	*tok = '>';

	if (ops->target.name == NULL)
		return -1;
find_target:
	target.addr = map__objdump_2mem(map, ops->target.addr);

	if (map_groups__find_ams(&target) == 0 &&
	    map__rip_2objdump(target.map, map->map_ip(target.map, target.addr)) == ops->target.addr)
		ops->target.sym = target.sym;

	return 0;

indirect_call:
	tok = strchr(endptr, '*');
	if (tok != NULL) {
		endptr++;

		/* Indirect call can use a non-rip register and offset: callq  *0x8(%rbx).
		 * Do not parse such instruction.  */
		if (strstr(endptr, "(%r") == NULL)
			ops->target.addr = strtoull(endptr, NULL, 16);
	}
	goto find_target;
}