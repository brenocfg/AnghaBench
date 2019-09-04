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
typedef  size_t u32 ;
struct svc_serv {int dummy; } ;
struct rpc_xprt {struct net* xprt_net; } ;
struct nfs_callback_data {int /*<<< orphan*/ * serv; int /*<<< orphan*/  users; } ;
struct net {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct svc_serv*) ; 
 int PTR_ERR (struct svc_serv*) ; 
 int /*<<< orphan*/  dprintk (char*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct svc_serv* nfs_callback_create_svc (size_t) ; 
 int /*<<< orphan*/  nfs_callback_down_net (size_t,struct svc_serv*,struct net*) ; 
 struct nfs_callback_data* nfs_callback_info ; 
 int /*<<< orphan*/  nfs_callback_mutex ; 
 int nfs_callback_start_svc (size_t,struct rpc_xprt*,struct svc_serv*) ; 
 int nfs_callback_up_net (size_t,struct svc_serv*,struct net*,struct rpc_xprt*) ; 
 int /*<<< orphan*/  svc_destroy (struct svc_serv*) ; 

int nfs_callback_up(u32 minorversion, struct rpc_xprt *xprt)
{
	struct svc_serv *serv;
	struct nfs_callback_data *cb_info = &nfs_callback_info[minorversion];
	int ret;
	struct net *net = xprt->xprt_net;

	mutex_lock(&nfs_callback_mutex);

	serv = nfs_callback_create_svc(minorversion);
	if (IS_ERR(serv)) {
		ret = PTR_ERR(serv);
		goto err_create;
	}

	ret = nfs_callback_up_net(minorversion, serv, net, xprt);
	if (ret < 0)
		goto err_net;

	ret = nfs_callback_start_svc(minorversion, xprt, serv);
	if (ret < 0)
		goto err_start;

	cb_info->users++;
	/*
	 * svc_create creates the svc_serv with sv_nrthreads == 1, and then
	 * svc_prepare_thread increments that. So we need to call svc_destroy
	 * on both success and failure so that the refcount is 1 when the
	 * thread exits.
	 */
err_net:
	if (!cb_info->users)
		cb_info->serv = NULL;
	svc_destroy(serv);
err_create:
	mutex_unlock(&nfs_callback_mutex);
	return ret;

err_start:
	nfs_callback_down_net(minorversion, serv, net);
	dprintk("NFS: Couldn't create server thread; err = %d\n", ret);
	goto err_net;
}