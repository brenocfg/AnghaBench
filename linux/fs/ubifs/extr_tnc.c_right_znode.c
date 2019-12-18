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
struct ubifs_znode {int level; int iip; int child_cnt; struct ubifs_znode* parent; } ;
struct ubifs_info {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct ubifs_znode*) ; 
 struct ubifs_znode* get_znode (struct ubifs_info*,struct ubifs_znode*,int) ; 

__attribute__((used)) static struct ubifs_znode *right_znode(struct ubifs_info *c,
				       struct ubifs_znode *znode)
{
	int level = znode->level;

	while (1) {
		int n = znode->iip + 1;

		/* Go up until we can go right */
		znode = znode->parent;
		if (!znode)
			return NULL;
		if (n < znode->child_cnt) {
			/* Now go down the leftmost branch to 'level' */
			znode = get_znode(c, znode, n);
			if (IS_ERR(znode))
				return znode;
			while (znode->level != level) {
				znode = get_znode(c, znode, 0);
				if (IS_ERR(znode))
					return znode;
			}
			break;
		}
	}
	return znode;
}