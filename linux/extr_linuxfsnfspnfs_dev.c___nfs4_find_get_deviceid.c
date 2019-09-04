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
struct nfs_server {int /*<<< orphan*/  nfs_client; int /*<<< orphan*/  pnfs_curr_ld; } ;
struct nfs4_deviceid_node {int /*<<< orphan*/  ref; } ;
struct nfs4_deviceid {int dummy; } ;

/* Variables and functions */
 struct nfs4_deviceid_node* _lookup_deviceid (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct nfs4_deviceid const*,long) ; 
 int /*<<< orphan*/  atomic_inc_not_zero (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

__attribute__((used)) static struct nfs4_deviceid_node *
__nfs4_find_get_deviceid(struct nfs_server *server,
		const struct nfs4_deviceid *id, long hash)
{
	struct nfs4_deviceid_node *d;

	rcu_read_lock();
	d = _lookup_deviceid(server->pnfs_curr_ld, server->nfs_client, id,
			hash);
	if (d != NULL && !atomic_inc_not_zero(&d->ref))
		d = NULL;
	rcu_read_unlock();
	return d;
}