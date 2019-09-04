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
struct ubifs_inode {char const* data; int /*<<< orphan*/  data_len; } ;
struct inode {int dummy; } ;
struct dentry {int dummy; } ;
struct delayed_call {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ECHILD ; 
 char const* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IS_ENCRYPTED (struct inode*) ; 
 char const* fscrypt_get_symlink (struct inode*,char const*,int /*<<< orphan*/ ,struct delayed_call*) ; 
 struct ubifs_inode* ubifs_inode (struct inode*) ; 

__attribute__((used)) static const char *ubifs_get_link(struct dentry *dentry,
					    struct inode *inode,
					    struct delayed_call *done)
{
	struct ubifs_inode *ui = ubifs_inode(inode);

	if (!IS_ENCRYPTED(inode))
		return ui->data;

	if (!dentry)
		return ERR_PTR(-ECHILD);

	return fscrypt_get_symlink(inode, ui->data, ui->data_len, done);
}