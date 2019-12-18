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
struct ceph_mds_client {int last_cap_flush_tid; int /*<<< orphan*/  nodename; void* pool_perm_tree; int /*<<< orphan*/  pool_perm_rwsem; int /*<<< orphan*/  snapid_map_lru; void* snapid_map_tree; int /*<<< orphan*/  snapid_map_lock; int /*<<< orphan*/  dentry_dir_leases; int /*<<< orphan*/  dentry_leases; int /*<<< orphan*/  dentry_list_lock; int /*<<< orphan*/  cap_reclaim_pending; int /*<<< orphan*/  cap_reclaim_work; int /*<<< orphan*/  cap_flushing_wq; int /*<<< orphan*/  cap_dirty_lock; scalar_t__ num_cap_flushing; int /*<<< orphan*/  cap_dirty_migrating; int /*<<< orphan*/  cap_dirty; int /*<<< orphan*/  cap_flush_list; int /*<<< orphan*/  snap_flush_lock; int /*<<< orphan*/  snap_flush_list; int /*<<< orphan*/  cap_delay_lock; int /*<<< orphan*/  cap_delay_list; int /*<<< orphan*/  last_renew_caps; int /*<<< orphan*/  delayed_work; void* request_tree; scalar_t__ oldest_tid; scalar_t__ last_tid; int /*<<< orphan*/  snap_empty_lock; scalar_t__ num_snap_realms; int /*<<< orphan*/  snap_empty; void* snap_realms; int /*<<< orphan*/  snap_rwsem; scalar_t__ last_snap_seq; int /*<<< orphan*/  quotarealms_inodes_mutex; void* quotarealms_inodes; int /*<<< orphan*/  quotarealms_count; scalar_t__ stopping; scalar_t__ max_sessions; int /*<<< orphan*/  num_sessions; int /*<<< orphan*/ * sessions; int /*<<< orphan*/  waiting_for_map; int /*<<< orphan*/  session_close_wq; int /*<<< orphan*/  safe_umount_waiters; void* mdsmap; int /*<<< orphan*/  mutex; struct ceph_fs_client* fsc; } ;
struct ceph_fs_client {int /*<<< orphan*/  mount_options; struct ceph_mds_client* mdsc; } ;
struct TYPE_2__ {int /*<<< orphan*/  nodename; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* RB_ROOT ; 
 int /*<<< orphan*/  atomic64_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ceph_adjust_caps_max_min (struct ceph_mds_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ceph_cap_reclaim_work ; 
 int /*<<< orphan*/  ceph_caps_init (struct ceph_mds_client*) ; 
 int /*<<< orphan*/  delayed_work ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_rwsem (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  kfree (struct ceph_mds_client*) ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strscpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 TYPE_1__* utsname () ; 

int ceph_mdsc_init(struct ceph_fs_client *fsc)

{
	struct ceph_mds_client *mdsc;

	mdsc = kzalloc(sizeof(struct ceph_mds_client), GFP_NOFS);
	if (!mdsc)
		return -ENOMEM;
	mdsc->fsc = fsc;
	mutex_init(&mdsc->mutex);
	mdsc->mdsmap = kzalloc(sizeof(*mdsc->mdsmap), GFP_NOFS);
	if (!mdsc->mdsmap) {
		kfree(mdsc);
		return -ENOMEM;
	}

	fsc->mdsc = mdsc;
	init_completion(&mdsc->safe_umount_waiters);
	init_waitqueue_head(&mdsc->session_close_wq);
	INIT_LIST_HEAD(&mdsc->waiting_for_map);
	mdsc->sessions = NULL;
	atomic_set(&mdsc->num_sessions, 0);
	mdsc->max_sessions = 0;
	mdsc->stopping = 0;
	atomic64_set(&mdsc->quotarealms_count, 0);
	mdsc->quotarealms_inodes = RB_ROOT;
	mutex_init(&mdsc->quotarealms_inodes_mutex);
	mdsc->last_snap_seq = 0;
	init_rwsem(&mdsc->snap_rwsem);
	mdsc->snap_realms = RB_ROOT;
	INIT_LIST_HEAD(&mdsc->snap_empty);
	mdsc->num_snap_realms = 0;
	spin_lock_init(&mdsc->snap_empty_lock);
	mdsc->last_tid = 0;
	mdsc->oldest_tid = 0;
	mdsc->request_tree = RB_ROOT;
	INIT_DELAYED_WORK(&mdsc->delayed_work, delayed_work);
	mdsc->last_renew_caps = jiffies;
	INIT_LIST_HEAD(&mdsc->cap_delay_list);
	spin_lock_init(&mdsc->cap_delay_lock);
	INIT_LIST_HEAD(&mdsc->snap_flush_list);
	spin_lock_init(&mdsc->snap_flush_lock);
	mdsc->last_cap_flush_tid = 1;
	INIT_LIST_HEAD(&mdsc->cap_flush_list);
	INIT_LIST_HEAD(&mdsc->cap_dirty);
	INIT_LIST_HEAD(&mdsc->cap_dirty_migrating);
	mdsc->num_cap_flushing = 0;
	spin_lock_init(&mdsc->cap_dirty_lock);
	init_waitqueue_head(&mdsc->cap_flushing_wq);
	INIT_WORK(&mdsc->cap_reclaim_work, ceph_cap_reclaim_work);
	atomic_set(&mdsc->cap_reclaim_pending, 0);

	spin_lock_init(&mdsc->dentry_list_lock);
	INIT_LIST_HEAD(&mdsc->dentry_leases);
	INIT_LIST_HEAD(&mdsc->dentry_dir_leases);

	ceph_caps_init(mdsc);
	ceph_adjust_caps_max_min(mdsc, fsc->mount_options);

	spin_lock_init(&mdsc->snapid_map_lock);
	mdsc->snapid_map_tree = RB_ROOT;
	INIT_LIST_HEAD(&mdsc->snapid_map_lru);

	init_rwsem(&mdsc->pool_perm_rwsem);
	mdsc->pool_perm_tree = RB_ROOT;

	strscpy(mdsc->nodename, utsname()->nodename,
		sizeof(mdsc->nodename));
	return 0;
}