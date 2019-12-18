#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct nfsd_net {int /*<<< orphan*/  reclaim_str_hashtbl_size; } ;
struct TYPE_4__ {struct nfs4_client_reclaim* data; } ;
struct TYPE_3__ {struct nfs4_client_reclaim* data; } ;
struct nfs4_client_reclaim {TYPE_2__ cr_princhash; TYPE_1__ cr_name; int /*<<< orphan*/  cr_strhash; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct nfs4_client_reclaim*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 

void
nfs4_remove_reclaim_record(struct nfs4_client_reclaim *crp, struct nfsd_net *nn)
{
	list_del(&crp->cr_strhash);
	kfree(crp->cr_name.data);
	kfree(crp->cr_princhash.data);
	kfree(crp);
	nn->reclaim_str_hashtbl_size--;
}