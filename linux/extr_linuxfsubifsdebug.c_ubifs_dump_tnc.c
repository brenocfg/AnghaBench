#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ubifs_znode {int level; } ;
struct TYPE_3__ {int /*<<< orphan*/  znode; } ;
struct ubifs_info {TYPE_1__ zroot; } ;
struct TYPE_4__ {int pid; } ;

/* Variables and functions */
 TYPE_2__* current ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 int /*<<< orphan*/  ubifs_dump_znode (struct ubifs_info*,struct ubifs_znode*) ; 
 struct ubifs_znode* ubifs_tnc_levelorder_next (struct ubifs_info*,int /*<<< orphan*/ ,struct ubifs_znode*) ; 

void ubifs_dump_tnc(struct ubifs_info *c)
{
	struct ubifs_znode *znode;
	int level;

	pr_err("\n");
	pr_err("(pid %d) start dumping TNC tree\n", current->pid);
	znode = ubifs_tnc_levelorder_next(c, c->zroot.znode, NULL);
	level = znode->level;
	pr_err("== Level %d ==\n", level);
	while (znode) {
		if (level != znode->level) {
			level = znode->level;
			pr_err("== Level %d ==\n", level);
		}
		ubifs_dump_znode(c, znode);
		znode = ubifs_tnc_levelorder_next(c, c->zroot.znode, znode);
	}
	pr_err("(pid %d) finish dumping TNC tree\n", current->pid);
}