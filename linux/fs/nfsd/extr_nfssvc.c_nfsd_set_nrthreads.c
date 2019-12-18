#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct nfsd_net {TYPE_2__* nfsd_serv; } ;
struct net {int dummy; } ;
struct TYPE_5__ {int sv_nrpools; int /*<<< orphan*/ * sv_pools; TYPE_1__* sv_ops; } ;
struct TYPE_4__ {int (* svo_setup ) (TYPE_2__*,int /*<<< orphan*/ *,int) ;} ;

/* Variables and functions */
 int NFSD_MAXSERVS ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int min (int,int) ; 
 int /*<<< orphan*/  mutex_is_locked (int /*<<< orphan*/ *) ; 
 struct nfsd_net* net_generic (struct net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfsd_destroy (struct net*) ; 
 int /*<<< orphan*/  nfsd_mutex ; 
 int /*<<< orphan*/  nfsd_net_id ; 
 int stub1 (TYPE_2__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  svc_get (TYPE_2__*) ; 

int nfsd_set_nrthreads(int n, int *nthreads, struct net *net)
{
	int i = 0;
	int tot = 0;
	int err = 0;
	struct nfsd_net *nn = net_generic(net, nfsd_net_id);

	WARN_ON(!mutex_is_locked(&nfsd_mutex));

	if (nn->nfsd_serv == NULL || n <= 0)
		return 0;

	if (n > nn->nfsd_serv->sv_nrpools)
		n = nn->nfsd_serv->sv_nrpools;

	/* enforce a global maximum number of threads */
	tot = 0;
	for (i = 0; i < n; i++) {
		nthreads[i] = min(nthreads[i], NFSD_MAXSERVS);
		tot += nthreads[i];
	}
	if (tot > NFSD_MAXSERVS) {
		/* total too large: scale down requested numbers */
		for (i = 0; i < n && tot > 0; i++) {
		    	int new = nthreads[i] * NFSD_MAXSERVS / tot;
			tot -= (nthreads[i] - new);
			nthreads[i] = new;
		}
		for (i = 0; i < n && tot > 0; i++) {
			nthreads[i]--;
			tot--;
		}
	}

	/*
	 * There must always be a thread in pool 0; the admin
	 * can't shut down NFS completely using pool_threads.
	 */
	if (nthreads[0] == 0)
		nthreads[0] = 1;

	/* apply the new numbers */
	svc_get(nn->nfsd_serv);
	for (i = 0; i < n; i++) {
		err = nn->nfsd_serv->sv_ops->svo_setup(nn->nfsd_serv,
				&nn->nfsd_serv->sv_pools[i], nthreads[i]);
		if (err)
			break;
	}
	nfsd_destroy(net);
	return err;
}