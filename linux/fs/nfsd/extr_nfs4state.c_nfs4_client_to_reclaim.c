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
struct xdr_netobj {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
struct nfsd_net {int /*<<< orphan*/  reclaim_str_hashtbl_size; int /*<<< orphan*/ * reclaim_str_hashtbl; } ;
struct TYPE_4__ {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
struct TYPE_3__ {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
struct nfs4_client_reclaim {int /*<<< orphan*/ * cr_clp; TYPE_2__ cr_princhash; TYPE_1__ cr_name; int /*<<< orphan*/  cr_strhash; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 struct nfs4_client_reclaim* alloc_reclaim () ; 
 unsigned int clientstr_hashval (struct xdr_netobj) ; 
 int /*<<< orphan*/  dprintk (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

struct nfs4_client_reclaim *
nfs4_client_to_reclaim(struct xdr_netobj name, struct xdr_netobj princhash,
		struct nfsd_net *nn)
{
	unsigned int strhashval;
	struct nfs4_client_reclaim *crp;

	dprintk("NFSD nfs4_client_to_reclaim NAME: %.*s\n", name.len, name.data);
	crp = alloc_reclaim();
	if (crp) {
		strhashval = clientstr_hashval(name);
		INIT_LIST_HEAD(&crp->cr_strhash);
		list_add(&crp->cr_strhash, &nn->reclaim_str_hashtbl[strhashval]);
		crp->cr_name.data = name.data;
		crp->cr_name.len = name.len;
		crp->cr_princhash.data = princhash.data;
		crp->cr_princhash.len = princhash.len;
		crp->cr_clp = NULL;
		nn->reclaim_str_hashtbl_size++;
	}
	return crp;
}