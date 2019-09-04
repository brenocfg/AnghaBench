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
 int /*<<< orphan*/  __forget_cached_acl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acl_by_type (struct inode*,int) ; 

void forget_cached_acl(struct inode *inode, int type)
{
	__forget_cached_acl(acl_by_type(inode, type));
}