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
struct net {int dummy; } ;
struct inode {TYPE_1__* i_sb; } ;
struct file {int dummy; } ;
struct TYPE_2__ {struct net* s_fs_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfsd_destroy (struct net*) ; 
 int /*<<< orphan*/  nfsd_mutex ; 
 int seq_release (struct inode*,struct file*) ; 

int nfsd_pool_stats_release(struct inode *inode, struct file *file)
{
	int ret = seq_release(inode, file);
	struct net *net = inode->i_sb->s_fs_info;

	mutex_lock(&nfsd_mutex);
	/* this function really, really should have been called svc_put() */
	nfsd_destroy(net);
	mutex_unlock(&nfsd_mutex);
	return ret;
}