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
struct inode {int /*<<< orphan*/  i_mode; } ;
struct dentry {int dummy; } ;
typedef  enum integrity_status { ____Placeholder_integrity_status } integrity_status ;

/* Variables and functions */
 int /*<<< orphan*/  S_ISREG (int /*<<< orphan*/ ) ; 
 struct inode* d_backing_inode (struct dentry*) ; 
 scalar_t__ evm_fixmode ; 
 int /*<<< orphan*/  evm_key_loaded () ; 
 int evm_verify_hmac (struct dentry*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static enum integrity_status evm_verify_current_integrity(struct dentry *dentry)
{
	struct inode *inode = d_backing_inode(dentry);

	if (!evm_key_loaded() || !S_ISREG(inode->i_mode) || evm_fixmode)
		return 0;
	return evm_verify_hmac(dentry, NULL, NULL, 0, NULL);
}