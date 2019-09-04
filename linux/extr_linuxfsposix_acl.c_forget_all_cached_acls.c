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
struct inode {int /*<<< orphan*/  i_default_acl; int /*<<< orphan*/  i_acl; } ;

/* Variables and functions */
 int /*<<< orphan*/  __forget_cached_acl (int /*<<< orphan*/ *) ; 

void forget_all_cached_acls(struct inode *inode)
{
	__forget_cached_acl(&inode->i_acl);
	__forget_cached_acl(&inode->i_default_acl);
}