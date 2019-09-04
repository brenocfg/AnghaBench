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
struct ubifs_znode {int iip; int child_cnt; struct ubifs_zbranch* zbranch; struct ubifs_znode* parent; } ;
struct ubifs_zbranch {scalar_t__ znode; } ;

/* Variables and functions */
 struct ubifs_znode* find_first_dirty (scalar_t__) ; 
 scalar_t__ ubifs_zn_dirty (scalar_t__) ; 

__attribute__((used)) static struct ubifs_znode *find_next_dirty(struct ubifs_znode *znode)
{
	int n = znode->iip + 1;

	znode = znode->parent;
	if (!znode)
		return NULL;
	for (; n < znode->child_cnt; n++) {
		struct ubifs_zbranch *zbr = &znode->zbranch[n];

		if (zbr->znode && ubifs_zn_dirty(zbr->znode))
			return find_first_dirty(zbr->znode);
	}
	return znode;
}