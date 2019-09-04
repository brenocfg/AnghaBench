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
struct svc_serv {TYPE_1__* sv_ops; } ;
struct nfs_callback_data {scalar_t__ users; struct svc_serv* serv; } ;
struct net {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* svo_setup ) (struct svc_serv*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  dprintk (char*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfs_callback_down_net (int,struct svc_serv*,struct net*) ; 
 struct nfs_callback_data* nfs_callback_info ; 
 int /*<<< orphan*/  nfs_callback_mutex ; 
 int /*<<< orphan*/  stub1 (struct svc_serv*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svc_destroy (struct svc_serv*) ; 
 int /*<<< orphan*/  svc_get (struct svc_serv*) ; 

void nfs_callback_down(int minorversion, struct net *net)
{
	struct nfs_callback_data *cb_info = &nfs_callback_info[minorversion];
	struct svc_serv *serv;

	mutex_lock(&nfs_callback_mutex);
	serv = cb_info->serv;
	nfs_callback_down_net(minorversion, serv, net);
	cb_info->users--;
	if (cb_info->users == 0) {
		svc_get(serv);
		serv->sv_ops->svo_setup(serv, NULL, 0);
		svc_destroy(serv);
		dprintk("nfs_callback_down: service destroyed\n");
		cb_info->serv = NULL;
	}
	mutex_unlock(&nfs_callback_mutex);
}