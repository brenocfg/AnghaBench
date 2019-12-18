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
struct dentry {int dummy; } ;
struct delayed_call {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_SYS_ADMIN ; 
 int /*<<< orphan*/  EPERM ; 
 char const* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 char const* proc_pid_get_link (struct dentry*,struct inode*,struct delayed_call*) ; 

__attribute__((used)) static const char *
proc_map_files_get_link(struct dentry *dentry,
			struct inode *inode,
		        struct delayed_call *done)
{
	if (!capable(CAP_SYS_ADMIN))
		return ERR_PTR(-EPERM);

	return proc_pid_get_link(dentry, inode, done);
}