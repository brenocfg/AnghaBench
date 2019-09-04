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
struct hfs_bnode {int /*<<< orphan*/  refcnt; int /*<<< orphan*/  this; TYPE_1__* tree; } ;
struct TYPE_2__ {int /*<<< orphan*/  cnid; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNODE_REFS ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hfs_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void hfs_bnode_get(struct hfs_bnode *node)
{
	if (node) {
		atomic_inc(&node->refcnt);
		hfs_dbg(BNODE_REFS, "get_node(%d:%d): %d\n",
			node->tree->cnid, node->this,
			atomic_read(&node->refcnt));
	}
}