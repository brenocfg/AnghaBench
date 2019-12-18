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
struct ovl_cu_creds {int /*<<< orphan*/ * new; int /*<<< orphan*/  old; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  override_creds (int /*<<< orphan*/ *) ; 
 int security_inode_copy_up (struct dentry*,int /*<<< orphan*/ **) ; 

__attribute__((used)) static int ovl_prep_cu_creds(struct dentry *dentry, struct ovl_cu_creds *cc)
{
	int err;

	cc->old = cc->new = NULL;
	err = security_inode_copy_up(dentry, &cc->new);
	if (err < 0)
		return err;

	if (cc->new)
		cc->old = override_creds(cc->new);

	return 0;
}