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
struct nfs4_stateowner {TYPE_1__* so_ops; int /*<<< orphan*/  so_count; struct nfs4_client* so_client; } ;
struct nfs4_client {int /*<<< orphan*/  cl_lock; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* so_unhash ) (struct nfs4_stateowner*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_dec_and_lock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  might_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfs4_free_stateowner (struct nfs4_stateowner*) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct nfs4_stateowner*) ; 

__attribute__((used)) static void nfs4_put_stateowner(struct nfs4_stateowner *sop)
{
	struct nfs4_client *clp = sop->so_client;

	might_lock(&clp->cl_lock);

	if (!atomic_dec_and_lock(&sop->so_count, &clp->cl_lock))
		return;
	sop->so_ops->so_unhash(sop);
	spin_unlock(&clp->cl_lock);
	nfs4_free_stateowner(sop);
}