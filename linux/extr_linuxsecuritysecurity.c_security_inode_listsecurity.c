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
 int /*<<< orphan*/  IS_PRIVATE (struct inode*) ; 
 int call_int_hook (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct inode*,char*,size_t) ; 
 int /*<<< orphan*/  inode_listsecurity ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

int security_inode_listsecurity(struct inode *inode, char *buffer, size_t buffer_size)
{
	if (unlikely(IS_PRIVATE(inode)))
		return 0;
	return call_int_hook(inode_listsecurity, 0, inode, buffer, buffer_size);
}