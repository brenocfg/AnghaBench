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
typedef  scalar_t__ u64 ;
struct symbol {int /*<<< orphan*/  end; int /*<<< orphan*/  start; } ;
struct map_symbol {struct symbol* sym; struct map* map; } ;
struct map {scalar_t__ (* unmap_ip ) (struct map*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* map_ip ) (struct map*,scalar_t__) ;} ;
struct TYPE_4__ {scalar_t__ addr; int outside; int offset_avail; scalar_t__ offset; int /*<<< orphan*/  sym; } ;
struct ins_operands {char const* raw; TYPE_2__ target; void* raw_comment; } ;
struct TYPE_3__ {char comment_char; } ;
struct arch {TYPE_1__ objdump; } ;
struct addr_map_symbol {scalar_t__ addr; int /*<<< orphan*/  sym; struct map* map; } ;

/* Variables and functions */
 scalar_t__ map__objdump_2mem (struct map*,scalar_t__) ; 
 scalar_t__ map__rip_2objdump (struct map*,int /*<<< orphan*/ ) ; 
 scalar_t__ map_groups__find_ams (struct addr_map_symbol*) ; 
 void* strchr (char const*,char) ; 
 void* strtoull (char const*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ stub1 (struct map*,int /*<<< orphan*/ ) ; 
 scalar_t__ stub2 (struct map*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (struct map*,scalar_t__) ; 
 char* validate_comma (char const*,struct ins_operands*) ; 

__attribute__((used)) static int jump__parse(struct arch *arch, struct ins_operands *ops, struct map_symbol *ms)
{
	struct map *map = ms->map;
	struct symbol *sym = ms->sym;
	struct addr_map_symbol target = {
		.map = map,
	};
	const char *c = strchr(ops->raw, ',');
	u64 start, end;

	ops->raw_comment = strchr(ops->raw, arch->objdump.comment_char);
	c = validate_comma(c, ops);

	/*
	 * Examples of lines to parse for the _cpp_lex_token@@Base
	 * function:
	 *
	 * 1159e6c: jne    115aa32 <_cpp_lex_token@@Base+0xf92>
	 * 1159e8b: jne    c469be <cpp_named_operator2name@@Base+0xa72>
	 *
	 * The first is a jump to an offset inside the same function,
	 * the second is to another function, i.e. that 0xa72 is an
	 * offset in the cpp_named_operator2name@@base function.
	 */
	/*
	 * skip over possible up to 2 operands to get to address, e.g.:
	 * tbnz	 w0, #26, ffff0000083cd190 <security_file_permission+0xd0>
	 */
	if (c++ != NULL) {
		ops->target.addr = strtoull(c, NULL, 16);
		if (!ops->target.addr) {
			c = strchr(c, ',');
			c = validate_comma(c, ops);
			if (c++ != NULL)
				ops->target.addr = strtoull(c, NULL, 16);
		}
	} else {
		ops->target.addr = strtoull(ops->raw, NULL, 16);
	}

	target.addr = map__objdump_2mem(map, ops->target.addr);
	start = map->unmap_ip(map, sym->start),
	end = map->unmap_ip(map, sym->end);

	ops->target.outside = target.addr < start || target.addr > end;

	/*
	 * FIXME: things like this in _cpp_lex_token (gcc's cc1 program):

		cpp_named_operator2name@@Base+0xa72

	 * Point to a place that is after the cpp_named_operator2name
	 * boundaries, i.e.  in the ELF symbol table for cc1
	 * cpp_named_operator2name is marked as being 32-bytes long, but it in
	 * fact is much larger than that, so we seem to need a symbols__find()
	 * routine that looks for >= current->start and  < next_symbol->start,
	 * possibly just for C++ objects?
	 *
	 * For now lets just make some progress by marking jumps to outside the
	 * current function as call like.
	 *
	 * Actual navigation will come next, with further understanding of how
	 * the symbol searching and disassembly should be done.
	 */
	if (map_groups__find_ams(&target) == 0 &&
	    map__rip_2objdump(target.map, map->map_ip(target.map, target.addr)) == ops->target.addr)
		ops->target.sym = target.sym;

	if (!ops->target.outside) {
		ops->target.offset = target.addr - start;
		ops->target.offset_avail = true;
	} else {
		ops->target.offset_avail = false;
	}

	return 0;
}