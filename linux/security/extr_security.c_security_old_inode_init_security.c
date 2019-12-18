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
struct qstr {int dummy; } ;
struct inode {int dummy; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  IS_PRIVATE (struct inode*) ; 
 int call_int_hook (int /*<<< orphan*/ ,int,struct inode*,struct inode*,struct qstr const*,char const**,void**,size_t*) ; 
 int /*<<< orphan*/  inode_init_security ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

int security_old_inode_init_security(struct inode *inode, struct inode *dir,
				     const struct qstr *qstr, const char **name,
				     void **value, size_t *len)
{
	if (unlikely(IS_PRIVATE(inode)))
		return -EOPNOTSUPP;
	return call_int_hook(inode_init_security, -EOPNOTSUPP, inode, dir,
			     qstr, name, value, len);
}