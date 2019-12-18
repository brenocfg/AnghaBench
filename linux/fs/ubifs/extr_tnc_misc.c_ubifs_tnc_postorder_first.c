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
struct ubifs_znode {scalar_t__ level; } ;

/* Variables and functions */
 struct ubifs_znode* ubifs_tnc_find_child (struct ubifs_znode*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

struct ubifs_znode *ubifs_tnc_postorder_first(struct ubifs_znode *znode)
{
	if (unlikely(!znode))
		return NULL;

	while (znode->level > 0) {
		struct ubifs_znode *child;

		child = ubifs_tnc_find_child(znode, 0);
		if (!child)
			return znode;
		znode = child;
	}

	return znode;
}