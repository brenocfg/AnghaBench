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
struct dentry {struct ceph_dentry_info* d_fsdata; } ;
struct ceph_dentry_info {int /*<<< orphan*/  lease_list; int /*<<< orphan*/  time; int /*<<< orphan*/ * lease_session; struct dentry* dentry; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ceph_dentry_cachep ; 
 int /*<<< orphan*/  jiffies ; 
 struct ceph_dentry_info* kmem_cache_zalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ceph_d_init(struct dentry *dentry)
{
	struct ceph_dentry_info *di;

	di = kmem_cache_zalloc(ceph_dentry_cachep, GFP_KERNEL);
	if (!di)
		return -ENOMEM;          /* oh well */

	di->dentry = dentry;
	di->lease_session = NULL;
	di->time = jiffies;
	dentry->d_fsdata = di;
	INIT_LIST_HEAD(&di->lease_list);
	return 0;
}