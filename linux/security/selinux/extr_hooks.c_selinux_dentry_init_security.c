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
typedef  int /*<<< orphan*/  u32 ;
struct qstr {int dummy; } ;
struct dentry {int /*<<< orphan*/  d_parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  current_cred () ; 
 int /*<<< orphan*/  d_inode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inode_mode_to_security_class (int) ; 
 int security_sid_to_context (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  selinux_cred (int /*<<< orphan*/ ) ; 
 int selinux_determine_inode_label (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct qstr const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  selinux_state ; 

__attribute__((used)) static int selinux_dentry_init_security(struct dentry *dentry, int mode,
					const struct qstr *name, void **ctx,
					u32 *ctxlen)
{
	u32 newsid;
	int rc;

	rc = selinux_determine_inode_label(selinux_cred(current_cred()),
					   d_inode(dentry->d_parent), name,
					   inode_mode_to_security_class(mode),
					   &newsid);
	if (rc)
		return rc;

	return security_sid_to_context(&selinux_state, newsid, (char **)ctx,
				       ctxlen);
}