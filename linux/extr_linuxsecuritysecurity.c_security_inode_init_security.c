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
struct xattr {int /*<<< orphan*/ * value; int /*<<< orphan*/  value_len; int /*<<< orphan*/  name; } ;
struct qstr {int dummy; } ;
struct inode {int dummy; } ;
typedef  int /*<<< orphan*/  new_xattrs ;
typedef  int (* initxattrs ) (struct inode*,struct xattr*,void*) ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  IS_PRIVATE (struct inode*) ; 
 int /*<<< orphan*/  MAX_LSM_EVM_XATTR ; 
 int call_int_hook (int /*<<< orphan*/ ,int,struct inode*,struct inode*,struct qstr const*,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int evm_inode_init_security (struct inode*,struct xattr*,struct xattr*) ; 
 int /*<<< orphan*/  inode_init_security ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct xattr*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

int security_inode_init_security(struct inode *inode, struct inode *dir,
				 const struct qstr *qstr,
				 const initxattrs initxattrs, void *fs_data)
{
	struct xattr new_xattrs[MAX_LSM_EVM_XATTR + 1];
	struct xattr *lsm_xattr, *evm_xattr, *xattr;
	int ret;

	if (unlikely(IS_PRIVATE(inode)))
		return 0;

	if (!initxattrs)
		return call_int_hook(inode_init_security, -EOPNOTSUPP, inode,
				     dir, qstr, NULL, NULL, NULL);
	memset(new_xattrs, 0, sizeof(new_xattrs));
	lsm_xattr = new_xattrs;
	ret = call_int_hook(inode_init_security, -EOPNOTSUPP, inode, dir, qstr,
						&lsm_xattr->name,
						&lsm_xattr->value,
						&lsm_xattr->value_len);
	if (ret)
		goto out;

	evm_xattr = lsm_xattr + 1;
	ret = evm_inode_init_security(inode, lsm_xattr, evm_xattr);
	if (ret)
		goto out;
	ret = initxattrs(inode, new_xattrs, fs_data);
out:
	for (xattr = new_xattrs; xattr->value != NULL; xattr++)
		kfree(xattr->value);
	return (ret == -EOPNOTSUPP) ? 0 : ret;
}