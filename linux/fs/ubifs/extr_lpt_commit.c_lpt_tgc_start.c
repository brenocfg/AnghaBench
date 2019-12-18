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
struct ubifs_info {int lpt_lebs; scalar_t__ lpt_first; scalar_t__ nhead_lnum; scalar_t__ leb_size; TYPE_1__* ltab; } ;
struct TYPE_2__ {scalar_t__ dirty; scalar_t__ free; int tgc; } ;

/* Variables and functions */
 int /*<<< orphan*/  dbg_lp (char*,scalar_t__) ; 

__attribute__((used)) static void lpt_tgc_start(struct ubifs_info *c)
{
	int i;

	for (i = 0; i < c->lpt_lebs; i++) {
		if (i + c->lpt_first == c->nhead_lnum)
			continue;
		if (c->ltab[i].dirty > 0 &&
		    c->ltab[i].free + c->ltab[i].dirty == c->leb_size) {
			c->ltab[i].tgc = 1;
			c->ltab[i].free = c->leb_size;
			c->ltab[i].dirty = 0;
			dbg_lp("LEB %d", i + c->lpt_first);
		}
	}
}