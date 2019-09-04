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
struct inode {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/ * acl_by_type (struct inode*,int) ; 
 struct posix_acl* rcu_dereference (int /*<<< orphan*/ ) ; 

struct posix_acl *get_cached_acl_rcu(struct inode *inode, int type)
{
	return rcu_dereference(*acl_by_type(inode, type));
}