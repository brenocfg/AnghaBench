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
struct nfs4_pnfs_ds {int /*<<< orphan*/  ds_node; int /*<<< orphan*/  ds_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  destroy_ds (struct nfs4_pnfs_ds*) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfs4_ds_cache_lock ; 
 scalar_t__ refcount_dec_and_lock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void nfs4_pnfs_ds_put(struct nfs4_pnfs_ds *ds)
{
	if (refcount_dec_and_lock(&ds->ds_count,
				&nfs4_ds_cache_lock)) {
		list_del_init(&ds->ds_node);
		spin_unlock(&nfs4_ds_cache_lock);
		destroy_ds(ds);
	}
}