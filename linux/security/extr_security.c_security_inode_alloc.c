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
struct inode {int dummy; } ;

/* Variables and functions */
 int call_int_hook (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct inode*) ; 
 int /*<<< orphan*/  inode_alloc_security ; 
 int lsm_inode_alloc (struct inode*) ; 
 int /*<<< orphan*/  security_inode_free (struct inode*) ; 
 scalar_t__ unlikely (int) ; 

int security_inode_alloc(struct inode *inode)
{
	int rc = lsm_inode_alloc(inode);

	if (unlikely(rc))
		return rc;
	rc = call_int_hook(inode_alloc_security, 0, inode);
	if (unlikely(rc))
		security_inode_free(inode);
	return rc;
}