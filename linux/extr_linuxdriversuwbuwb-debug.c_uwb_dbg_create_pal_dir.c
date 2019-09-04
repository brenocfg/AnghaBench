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
struct uwb_rc {TYPE_1__* dbg; } ;
struct uwb_pal {scalar_t__ name; struct uwb_rc* rc; } ;
struct dentry {int dummy; } ;
struct TYPE_2__ {scalar_t__ root_d; } ;

/* Variables and functions */
 struct dentry* debugfs_create_dir (scalar_t__,scalar_t__) ; 
 scalar_t__ root_dir ; 

struct dentry *uwb_dbg_create_pal_dir(struct uwb_pal *pal)
{
	struct uwb_rc *rc = pal->rc;

	if (root_dir && rc->dbg && rc->dbg->root_d && pal->name)
		return debugfs_create_dir(pal->name, rc->dbg->root_d);
	return NULL;
}