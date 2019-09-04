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
struct dentry {int /*<<< orphan*/  d_sb; } ;
struct cred {int dummy; } ;

/* Variables and functions */
 struct cred* ovl_override_creds (int /*<<< orphan*/ ) ; 
 int ovl_set_redirect (struct dentry*,int) ; 
 int /*<<< orphan*/  revert_creds (struct cred const*) ; 

__attribute__((used)) static int ovl_set_link_redirect(struct dentry *dentry)
{
	const struct cred *old_cred;
	int err;

	old_cred = ovl_override_creds(dentry->d_sb);
	err = ovl_set_redirect(dentry, false);
	revert_creds(old_cred);

	return err;
}