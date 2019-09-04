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
typedef  int /*<<< orphan*/  handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  ext4_initxattrs ; 
 int security_inode_init_security (struct inode*,struct inode*,struct qstr const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int
ext4_init_security(handle_t *handle, struct inode *inode, struct inode *dir,
		   const struct qstr *qstr)
{
	return security_inode_init_security(inode, dir, qstr,
					    &ext4_initxattrs, handle);
}