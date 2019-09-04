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
struct svc_serv {int sv_nrthreads; TYPE_1__* sv_ops; } ;
struct rpc_xprt {int dummy; } ;
struct TYPE_2__ {int (* svo_setup ) (struct svc_serv*,int /*<<< orphan*/ *,int) ;} ;

/* Variables and functions */
 int NFS4_MIN_NR_CALLBACK_THREADS ; 
 int /*<<< orphan*/  dprintk (char*) ; 
 int /*<<< orphan*/  nfs_callback_bc_serv (int,struct rpc_xprt*,struct svc_serv*) ; 
 int nfs_callback_nr_threads ; 
 int stub1 (struct svc_serv*,int /*<<< orphan*/ *,int) ; 
 int stub2 (struct svc_serv*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int nfs_callback_start_svc(int minorversion, struct rpc_xprt *xprt,
				  struct svc_serv *serv)
{
	int nrservs = nfs_callback_nr_threads;
	int ret;

	nfs_callback_bc_serv(minorversion, xprt, serv);

	if (nrservs < NFS4_MIN_NR_CALLBACK_THREADS)
		nrservs = NFS4_MIN_NR_CALLBACK_THREADS;

	if (serv->sv_nrthreads-1 == nrservs)
		return 0;

	ret = serv->sv_ops->svo_setup(serv, NULL, nrservs);
	if (ret) {
		serv->sv_ops->svo_setup(serv, NULL, 0);
		return ret;
	}
	dprintk("nfs_callback_up: service started\n");
	return 0;
}