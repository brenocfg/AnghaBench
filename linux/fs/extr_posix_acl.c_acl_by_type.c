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
struct posix_acl {int dummy; } ;
struct inode {struct posix_acl* i_default_acl; struct posix_acl* i_acl; } ;

/* Variables and functions */
#define  ACL_TYPE_ACCESS 129 
#define  ACL_TYPE_DEFAULT 128 
 int /*<<< orphan*/  BUG () ; 

__attribute__((used)) static struct posix_acl **acl_by_type(struct inode *inode, int type)
{
	switch (type) {
	case ACL_TYPE_ACCESS:
		return &inode->i_acl;
	case ACL_TYPE_DEFAULT:
		return &inode->i_default_acl;
	default:
		BUG();
	}
}