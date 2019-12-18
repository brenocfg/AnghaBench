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
struct nfsd_net {int /*<<< orphan*/  client_lock; } ;
struct TYPE_4__ {TYPE_1__* so_client; } ;
struct nfs4_openowner {struct nfs4_ol_stateid* oo_last_closed_stid; int /*<<< orphan*/  oo_close_lru; TYPE_2__ oo_owner; } ;
struct nfs4_ol_stateid {int /*<<< orphan*/  st_stid; } ;
struct TYPE_3__ {int /*<<< orphan*/  net; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 struct nfsd_net* net_generic (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs4_put_stid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfsd_net_id ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void release_last_closed_stateid(struct nfs4_openowner *oo)
{
	struct nfsd_net *nn = net_generic(oo->oo_owner.so_client->net,
					  nfsd_net_id);
	struct nfs4_ol_stateid *s;

	spin_lock(&nn->client_lock);
	s = oo->oo_last_closed_stid;
	if (s) {
		list_del_init(&oo->oo_close_lru);
		oo->oo_last_closed_stid = NULL;
	}
	spin_unlock(&nn->client_lock);
	if (s)
		nfs4_put_stid(&s->st_stid);
}