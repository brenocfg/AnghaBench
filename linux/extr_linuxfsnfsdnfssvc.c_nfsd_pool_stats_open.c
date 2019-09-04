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
struct nfsd_net {int /*<<< orphan*/ * nfsd_serv; } ;
struct inode {TYPE_1__* i_sb; } ;
struct file {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  s_fs_info; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct nfsd_net* net_generic (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfsd_mutex ; 
 int /*<<< orphan*/  nfsd_net_id ; 
 int /*<<< orphan*/  svc_get (int /*<<< orphan*/ *) ; 
 int svc_pool_stats_open (int /*<<< orphan*/ *,struct file*) ; 

int nfsd_pool_stats_open(struct inode *inode, struct file *file)
{
	int ret;
	struct nfsd_net *nn = net_generic(inode->i_sb->s_fs_info, nfsd_net_id);

	mutex_lock(&nfsd_mutex);
	if (nn->nfsd_serv == NULL) {
		mutex_unlock(&nfsd_mutex);
		return -ENODEV;
	}
	/* bump up the psudo refcount while traversing */
	svc_get(nn->nfsd_serv);
	ret = svc_pool_stats_open(nn->nfsd_serv, file);
	mutex_unlock(&nfsd_mutex);
	return ret;
}