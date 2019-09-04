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
struct pnfs_layoutdriver_type {int dummy; } ;
struct nfs_client {int dummy; } ;
struct nfs4_deviceid_node {int /*<<< orphan*/  flags; int /*<<< orphan*/  node; } ;
struct nfs4_deviceid {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFS_DEVICEID_NOCACHE ; 
 struct nfs4_deviceid_node* _lookup_deviceid (struct pnfs_layoutdriver_type const*,struct nfs_client const*,struct nfs4_deviceid const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hlist_del_init_rcu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfs4_deviceid_hash (struct nfs4_deviceid const*) ; 
 int /*<<< orphan*/  nfs4_deviceid_lock ; 
 int /*<<< orphan*/  nfs4_put_deviceid_node (struct nfs4_deviceid_node*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void
nfs4_delete_deviceid(const struct pnfs_layoutdriver_type *ld,
			 const struct nfs_client *clp, const struct nfs4_deviceid *id)
{
	struct nfs4_deviceid_node *d;

	spin_lock(&nfs4_deviceid_lock);
	rcu_read_lock();
	d = _lookup_deviceid(ld, clp, id, nfs4_deviceid_hash(id));
	rcu_read_unlock();
	if (!d) {
		spin_unlock(&nfs4_deviceid_lock);
		return;
	}
	hlist_del_init_rcu(&d->node);
	clear_bit(NFS_DEVICEID_NOCACHE, &d->flags);
	spin_unlock(&nfs4_deviceid_lock);

	/* balance the initial ref set in pnfs_insert_deviceid */
	nfs4_put_deviceid_node(d);
}