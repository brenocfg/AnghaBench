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
struct xdr_netobj {int dummy; } ;
struct nfsd_net {int /*<<< orphan*/  unconf_name_tree; int /*<<< orphan*/  client_lock; } ;
struct nfs4_client {int dummy; } ;

/* Variables and functions */
 struct nfs4_client* find_clp_in_name_tree (struct xdr_netobj*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct nfs4_client *
find_unconfirmed_client_by_name(struct xdr_netobj *name, struct nfsd_net *nn)
{
	lockdep_assert_held(&nn->client_lock);
	return find_clp_in_name_tree(name, &nn->unconf_name_tree);
}