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
struct nfsd_net {int /*<<< orphan*/  conf_name_tree; int /*<<< orphan*/  unconf_name_tree; int /*<<< orphan*/ * conf_id_hashtbl; int /*<<< orphan*/  client_lock; } ;
struct TYPE_2__ {int /*<<< orphan*/  cl_id; } ;
struct nfs4_client {int /*<<< orphan*/  cl_flags; int /*<<< orphan*/  cl_namenode; int /*<<< orphan*/  cl_idhash; int /*<<< orphan*/  net; TYPE_1__ cl_clientid; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFSD4_CLIENT_CONFIRMED ; 
 int /*<<< orphan*/  add_clp_to_name_tree (struct nfs4_client*,int /*<<< orphan*/ *) ; 
 unsigned int clientid_hashval (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dprintk (char*,struct nfs4_client*) ; 
 int /*<<< orphan*/  list_move (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 struct nfsd_net* net_generic (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfsd_net_id ; 
 int /*<<< orphan*/  rb_erase (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  renew_client_locked (struct nfs4_client*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
move_to_confirmed(struct nfs4_client *clp)
{
	unsigned int idhashval = clientid_hashval(clp->cl_clientid.cl_id);
	struct nfsd_net *nn = net_generic(clp->net, nfsd_net_id);

	lockdep_assert_held(&nn->client_lock);

	dprintk("NFSD: move_to_confirm nfs4_client %p\n", clp);
	list_move(&clp->cl_idhash, &nn->conf_id_hashtbl[idhashval]);
	rb_erase(&clp->cl_namenode, &nn->unconf_name_tree);
	add_clp_to_name_tree(clp, &nn->conf_name_tree);
	set_bit(NFSD4_CLIENT_CONFIRMED, &clp->cl_flags);
	renew_client_locked(clp);
}