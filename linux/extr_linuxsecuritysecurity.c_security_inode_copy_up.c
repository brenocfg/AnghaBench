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
struct dentry {int dummy; } ;
struct cred {int dummy; } ;

/* Variables and functions */
 int call_int_hook (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct dentry*,struct cred**) ; 
 int /*<<< orphan*/  inode_copy_up ; 

int security_inode_copy_up(struct dentry *src, struct cred **new)
{
	return call_int_hook(inode_copy_up, 0, src, new);
}