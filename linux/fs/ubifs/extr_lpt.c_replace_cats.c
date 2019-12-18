#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ubifs_pnode {TYPE_1__* lprops; } ;
struct ubifs_info {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  lnum; } ;

/* Variables and functions */
 int UBIFS_LPT_FANOUT ; 
 int /*<<< orphan*/  ubifs_replace_cat (struct ubifs_info*,TYPE_1__*,TYPE_1__*) ; 

__attribute__((used)) static void replace_cats(struct ubifs_info *c, struct ubifs_pnode *old_pnode,
			 struct ubifs_pnode *new_pnode)
{
	int i;

	for (i = 0; i < UBIFS_LPT_FANOUT; i++) {
		if (!new_pnode->lprops[i].lnum)
			return;
		ubifs_replace_cat(c, &old_pnode->lprops[i],
				  &new_pnode->lprops[i]);
	}
}