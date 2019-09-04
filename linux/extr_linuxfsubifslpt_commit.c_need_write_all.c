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
struct ubifs_info {int lpt_lebs; scalar_t__ lpt_first; scalar_t__ nhead_lnum; scalar_t__ leb_size; scalar_t__ nhead_offs; int lpt_sz; TYPE_1__* ltab; } ;
struct TYPE_2__ {scalar_t__ free; scalar_t__ dirty; } ;

/* Variables and functions */

__attribute__((used)) static int need_write_all(struct ubifs_info *c)
{
	long long free = 0;
	int i;

	for (i = 0; i < c->lpt_lebs; i++) {
		if (i + c->lpt_first == c->nhead_lnum)
			free += c->leb_size - c->nhead_offs;
		else if (c->ltab[i].free == c->leb_size)
			free += c->leb_size;
		else if (c->ltab[i].free + c->ltab[i].dirty == c->leb_size)
			free += c->leb_size;
	}
	/* Less than twice the size left */
	if (free <= c->lpt_sz * 2)
		return 1;
	return 0;
}