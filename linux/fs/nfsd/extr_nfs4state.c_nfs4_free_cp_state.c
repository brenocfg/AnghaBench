#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct nfsd_net {int /*<<< orphan*/  s2s_cp_lock; int /*<<< orphan*/  s2s_cp_stateids; } ;
struct TYPE_5__ {int /*<<< orphan*/  so_id; } ;
struct TYPE_6__ {TYPE_2__ si_opaque; } ;
struct nfsd4_copy {TYPE_3__ cp_stateid; TYPE_1__* cp_clp; } ;
struct TYPE_4__ {int /*<<< orphan*/  net; } ;

/* Variables and functions */
 int /*<<< orphan*/  idr_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct nfsd_net* net_generic (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfsd_net_id ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void nfs4_free_cp_state(struct nfsd4_copy *copy)
{
	struct nfsd_net *nn;

	nn = net_generic(copy->cp_clp->net, nfsd_net_id);
	spin_lock(&nn->s2s_cp_lock);
	idr_remove(&nn->s2s_cp_stateids, copy->cp_stateid.si_opaque.so_id);
	spin_unlock(&nn->s2s_cp_lock);
}