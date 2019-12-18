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
struct cyc_hist {int /*<<< orphan*/  num_aggr; int /*<<< orphan*/  num; int /*<<< orphan*/  cycles_aggr; int /*<<< orphan*/  cycles; int /*<<< orphan*/  start; } ;
struct block_info {int end; int /*<<< orphan*/  num_aggr; int /*<<< orphan*/  num; int /*<<< orphan*/  cycles_aggr; int /*<<< orphan*/  cycles; int /*<<< orphan*/  start; struct symbol* sym; } ;

/* Variables and functions */

__attribute__((used)) static void init_block_info(struct block_info *bi, struct symbol *sym,
			    struct cyc_hist *ch, int offset)
{
	bi->sym = sym;
	bi->start = ch->start;
	bi->end = offset;
	bi->cycles = ch->cycles;
	bi->cycles_aggr = ch->cycles_aggr;
	bi->num = ch->num;
	bi->num_aggr = ch->num_aggr;
}