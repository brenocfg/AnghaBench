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
struct nfs_net {int /*<<< orphan*/  nfs_client_lock; int /*<<< orphan*/  cb_ident_idr; } ;
struct nfs_client {int cl_cb_ident; TYPE_1__* rpc_ops; int /*<<< orphan*/  cl_net; } ;
struct TYPE_2__ {int version; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GFP_NOWAIT ; 
 int idr_alloc (int /*<<< orphan*/ *,struct nfs_client*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  idr_preload (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  idr_preload_end () ; 
 struct nfs_net* net_generic (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_net_id ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int nfs_get_cb_ident_idr(struct nfs_client *clp, int minorversion)
{
	int ret = 0;
	struct nfs_net *nn = net_generic(clp->cl_net, nfs_net_id);

	if (clp->rpc_ops->version != 4 || minorversion != 0)
		return ret;
	idr_preload(GFP_KERNEL);
	spin_lock(&nn->nfs_client_lock);
	ret = idr_alloc(&nn->cb_ident_idr, clp, 1, 0, GFP_NOWAIT);
	if (ret >= 0)
		clp->cl_cb_ident = ret;
	spin_unlock(&nn->nfs_client_lock);
	idr_preload_end();
	return ret < 0 ? ret : 0;
}