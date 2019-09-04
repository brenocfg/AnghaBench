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
struct hist_entry_iter {int curr; int total; struct branch_info* priv; } ;
struct TYPE_2__ {int /*<<< orphan*/  addr; int /*<<< orphan*/  sym; int /*<<< orphan*/  map; } ;
struct branch_info {TYPE_1__ to; } ;
struct addr_location {int /*<<< orphan*/  addr; int /*<<< orphan*/  sym; int /*<<< orphan*/  map; } ;

/* Variables and functions */

__attribute__((used)) static int
iter_next_branch_entry(struct hist_entry_iter *iter, struct addr_location *al)
{
	struct branch_info *bi = iter->priv;
	int i = iter->curr;

	if (bi == NULL)
		return 0;

	if (iter->curr >= iter->total)
		return 0;

	al->map = bi[i].to.map;
	al->sym = bi[i].to.sym;
	al->addr = bi[i].to.addr;
	return 1;
}