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
struct xattr {int value_len; int /*<<< orphan*/  name; struct evm_xattr* value; } ;
struct inode {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  type; } ;
struct evm_xattr {int /*<<< orphan*/  digest; TYPE_1__ data; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  EVM_XATTR_HMAC ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  XATTR_EVM_SUFFIX ; 
 int evm_init_hmac (struct inode*,struct xattr const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  evm_key_loaded () ; 
 int /*<<< orphan*/  evm_protected_xattr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct evm_xattr*) ; 
 struct evm_xattr* kzalloc (int,int /*<<< orphan*/ ) ; 

int evm_inode_init_security(struct inode *inode,
				 const struct xattr *lsm_xattr,
				 struct xattr *evm_xattr)
{
	struct evm_xattr *xattr_data;
	int rc;

	if (!evm_key_loaded() || !evm_protected_xattr(lsm_xattr->name))
		return 0;

	xattr_data = kzalloc(sizeof(*xattr_data), GFP_NOFS);
	if (!xattr_data)
		return -ENOMEM;

	xattr_data->data.type = EVM_XATTR_HMAC;
	rc = evm_init_hmac(inode, lsm_xattr, xattr_data->digest);
	if (rc < 0)
		goto out;

	evm_xattr->value = xattr_data;
	evm_xattr->value_len = sizeof(*xattr_data);
	evm_xattr->name = XATTR_EVM_SUFFIX;
	return 0;
out:
	kfree(xattr_data);
	return rc;
}