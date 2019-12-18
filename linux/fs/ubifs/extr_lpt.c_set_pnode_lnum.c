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
struct ubifs_pnode {int num; TYPE_1__* lprops; } ;
struct ubifs_info {int main_first; int leb_cnt; } ;
struct TYPE_2__ {int /*<<< orphan*/  lnum; } ;

/* Variables and functions */
 int UBIFS_LPT_FANOUT ; 
 int UBIFS_LPT_FANOUT_SHIFT ; 

__attribute__((used)) static void set_pnode_lnum(const struct ubifs_info *c,
			   struct ubifs_pnode *pnode)
{
	int i, lnum;

	lnum = (pnode->num << UBIFS_LPT_FANOUT_SHIFT) + c->main_first;
	for (i = 0; i < UBIFS_LPT_FANOUT; i++) {
		if (lnum >= c->leb_cnt)
			return;
		pnode->lprops[i].lnum = lnum++;
	}
}