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
struct symbol {int dummy; } ;
struct branch_flags {scalar_t__ predicted; } ;
struct block_range_iter {int dummy; } ;
struct block_range {int /*<<< orphan*/  pred; int /*<<< orphan*/  taken; int /*<<< orphan*/  is_branch; int /*<<< orphan*/  coverage; struct symbol* sym; int /*<<< orphan*/  entry; int /*<<< orphan*/  is_target; } ;
struct annotation {int /*<<< orphan*/  max_coverage; } ;
struct addr_map_symbol {scalar_t__ addr; struct symbol* sym; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 struct block_range_iter block_range__create (scalar_t__,scalar_t__) ; 
 struct block_range* block_range_iter (struct block_range_iter*) ; 
 scalar_t__ block_range_iter__next (struct block_range_iter*) ; 
 int /*<<< orphan*/  block_range_iter__valid (struct block_range_iter*) ; 
 int /*<<< orphan*/  max (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct annotation* symbol__annotation (struct symbol*) ; 

__attribute__((used)) static void process_basic_block(struct addr_map_symbol *start,
				struct addr_map_symbol *end,
				struct branch_flags *flags)
{
	struct symbol *sym = start->sym;
	struct annotation *notes = sym ? symbol__annotation(sym) : NULL;
	struct block_range_iter iter;
	struct block_range *entry;

	/*
	 * Sanity; NULL isn't executable and the CPU cannot execute backwards
	 */
	if (!start->addr || start->addr > end->addr)
		return;

	iter = block_range__create(start->addr, end->addr);
	if (!block_range_iter__valid(&iter))
		return;

	/*
	 * First block in range is a branch target.
	 */
	entry = block_range_iter(&iter);
	assert(entry->is_target);
	entry->entry++;

	do {
		entry = block_range_iter(&iter);

		entry->coverage++;
		entry->sym = sym;

		if (notes)
			notes->max_coverage = max(notes->max_coverage, entry->coverage);

	} while (block_range_iter__next(&iter));

	/*
	 * Last block in rage is a branch.
	 */
	entry = block_range_iter(&iter);
	assert(entry->is_branch);
	entry->taken++;
	if (flags->predicted)
		entry->pred++;
}