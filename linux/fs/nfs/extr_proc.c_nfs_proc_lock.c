#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct inode {int dummy; } ;
struct file_lock {int dummy; } ;
struct file {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  nlm_host; } ;

/* Variables and functions */
 TYPE_1__* NFS_SERVER (struct inode*) ; 
 struct inode* file_inode (struct file*) ; 
 int nlmclnt_proc (int /*<<< orphan*/ ,int,struct file_lock*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
nfs_proc_lock(struct file *filp, int cmd, struct file_lock *fl)
{
	struct inode *inode = file_inode(filp);

	return nlmclnt_proc(NFS_SERVER(inode)->nlm_host, cmd, fl, NULL);
}