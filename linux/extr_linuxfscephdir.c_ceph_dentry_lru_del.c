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
struct dentry {int /*<<< orphan*/  d_sb; } ;
struct ceph_mds_client {int /*<<< orphan*/  dentry_lru_lock; int /*<<< orphan*/  num_dentry; } ;
struct ceph_dentry_info {int /*<<< orphan*/  lru; } ;
struct TYPE_2__ {struct ceph_mds_client* mdsc; } ;

/* Variables and functions */
 struct ceph_dentry_info* ceph_dentry (struct dentry*) ; 
 TYPE_1__* ceph_sb_to_client (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dout (char*,struct ceph_dentry_info*,struct dentry*,struct dentry*) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void ceph_dentry_lru_del(struct dentry *dn)
{
	struct ceph_dentry_info *di = ceph_dentry(dn);
	struct ceph_mds_client *mdsc;

	dout("dentry_lru_del %p %p '%pd'\n", di, dn, dn);
	mdsc = ceph_sb_to_client(dn->d_sb)->mdsc;
	spin_lock(&mdsc->dentry_lru_lock);
	list_del_init(&di->lru);
	mdsc->num_dentry--;
	spin_unlock(&mdsc->dentry_lru_lock);
}