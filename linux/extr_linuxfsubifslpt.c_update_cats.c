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
struct ubifs_pnode {TYPE_1__* lprops; } ;
struct ubifs_info {int dummy; } ;
struct TYPE_2__ {int flags; int lnum; } ;

/* Variables and functions */
 int LPROPS_CAT_MASK ; 
 int UBIFS_LPT_FANOUT ; 
 int /*<<< orphan*/  ubifs_add_to_cat (struct ubifs_info*,TYPE_1__*,int) ; 

__attribute__((used)) static void update_cats(struct ubifs_info *c, struct ubifs_pnode *pnode)
{
	int i;

	for (i = 0; i < UBIFS_LPT_FANOUT; i++) {
		int cat = pnode->lprops[i].flags & LPROPS_CAT_MASK;
		int lnum = pnode->lprops[i].lnum;

		if (!lnum)
			return;
		ubifs_add_to_cat(c, &pnode->lprops[i], cat);
	}
}