#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ovl_entry {int numlower; TYPE_3__* lowerstack; } ;
struct dentry {TYPE_1__* d_sb; } ;
struct TYPE_6__ {TYPE_2__* layer; } ;
struct TYPE_5__ {int idx; } ;
struct TYPE_4__ {struct dentry* s_root; } ;

/* Variables and functions */
 struct ovl_entry* OVL_E (struct dentry*) ; 
 int /*<<< orphan*/  OVL_INDEX ; 
 int /*<<< orphan*/  d_inode (struct dentry*) ; 
 scalar_t__ ovl_dentry_upper (struct dentry*) ; 
 int /*<<< orphan*/  ovl_test_flag (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ovl_connectable_layer(struct dentry *dentry)
{
	struct ovl_entry *oe = OVL_E(dentry);

	/* We can get overlay root from root of any layer */
	if (dentry == dentry->d_sb->s_root)
		return oe->numlower;

	/*
	 * If it's an unindexed merge dir, then it's not connectable with any
	 * lower layer
	 */
	if (ovl_dentry_upper(dentry) &&
	    !ovl_test_flag(OVL_INDEX, d_inode(dentry)))
		return 0;

	/* We can get upper/overlay path from indexed/lower dentry */
	return oe->lowerstack[0].layer->idx;
}