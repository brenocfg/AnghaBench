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
struct ovl_inode {char const* redirect; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 struct ovl_inode* OVL_I (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  d_inode (struct dentry*) ; 
 int /*<<< orphan*/  kfree (char const*) ; 

void ovl_dentry_set_redirect(struct dentry *dentry, const char *redirect)
{
	struct ovl_inode *oi = OVL_I(d_inode(dentry));

	kfree(oi->redirect);
	oi->redirect = redirect;
}