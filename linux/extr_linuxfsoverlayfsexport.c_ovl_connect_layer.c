#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct dentry {TYPE_1__* d_sb; } ;
struct TYPE_8__ {TYPE_3__* lowerstack; } ;
struct TYPE_7__ {TYPE_2__* layer; } ;
struct TYPE_6__ {int idx; } ;
struct TYPE_5__ {struct dentry* s_root; } ;

/* Variables and functions */
 int EIO ; 
 TYPE_4__* OVL_E (struct dentry*) ; 
 int /*<<< orphan*/  OVL_E_CONNECTED ; 
 int /*<<< orphan*/  OVL_INDEX ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  d_inode (struct dentry*) ; 
 struct dentry* dget (struct dentry*) ; 
 struct dentry* dget_parent (struct dentry*) ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 
 int ovl_connectable_layer (struct dentry*) ; 
 int /*<<< orphan*/  ovl_dentry_lower (struct dentry*) ; 
 int /*<<< orphan*/  ovl_dentry_set_flag (int /*<<< orphan*/ ,struct dentry*) ; 
 scalar_t__ ovl_dentry_test_flag (int /*<<< orphan*/ ,struct dentry*) ; 
 int ovl_encode_maybe_copy_up (struct dentry*) ; 
 scalar_t__ ovl_test_flag (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ovl_connect_layer(struct dentry *dentry)
{
	struct dentry *next, *parent = NULL;
	int origin_layer;
	int err = 0;

	if (WARN_ON(dentry == dentry->d_sb->s_root) ||
	    WARN_ON(!ovl_dentry_lower(dentry)))
		return -EIO;

	origin_layer = OVL_E(dentry)->lowerstack[0].layer->idx;
	if (ovl_dentry_test_flag(OVL_E_CONNECTED, dentry))
		return origin_layer;

	/* Find the topmost origin layer connectable ancestor of @dentry */
	next = dget(dentry);
	for (;;) {
		parent = dget_parent(next);
		if (WARN_ON(parent == next)) {
			err = -EIO;
			break;
		}

		/*
		 * If @parent is not origin layer connectable, then copy up
		 * @next which is origin layer connectable and we are done.
		 */
		if (ovl_connectable_layer(parent) < origin_layer) {
			err = ovl_encode_maybe_copy_up(next);
			break;
		}

		/* If @parent is connected or indexed we are done */
		if (ovl_dentry_test_flag(OVL_E_CONNECTED, parent) ||
		    ovl_test_flag(OVL_INDEX, d_inode(parent)))
			break;

		dput(next);
		next = parent;
	}

	dput(parent);
	dput(next);

	if (!err)
		ovl_dentry_set_flag(OVL_E_CONNECTED, dentry);

	return err ?: origin_layer;
}