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
struct inode {int dummy; } ;
struct dentry {int /*<<< orphan*/  d_sb; } ;
struct delayed_call {int dummy; } ;
struct autofs_sb_info {int dummy; } ;
struct autofs_info {int /*<<< orphan*/  last_used; } ;
struct TYPE_2__ {char const* i_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  ECHILD ; 
 char const* ERR_PTR (int /*<<< orphan*/ ) ; 
 struct autofs_info* autofs_dentry_ino (struct dentry*) ; 
 int /*<<< orphan*/  autofs_oz_mode (struct autofs_sb_info*) ; 
 struct autofs_sb_info* autofs_sbi (int /*<<< orphan*/ ) ; 
 TYPE_1__* d_inode (struct dentry*) ; 
 int /*<<< orphan*/  jiffies ; 

__attribute__((used)) static const char *autofs_get_link(struct dentry *dentry,
				   struct inode *inode,
				   struct delayed_call *done)
{
	struct autofs_sb_info *sbi;
	struct autofs_info *ino;

	if (!dentry)
		return ERR_PTR(-ECHILD);
	sbi = autofs_sbi(dentry->d_sb);
	ino = autofs_dentry_ino(dentry);
	if (ino && !autofs_oz_mode(sbi))
		ino->last_used = jiffies;
	return d_inode(dentry)->i_private;
}