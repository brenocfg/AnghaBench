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
struct TYPE_3__ {int /*<<< orphan*/  kset; } ;
struct TYPE_4__ {TYPE_1__ kobject; } ;
struct xfs_mount {int m_finobt_nores; TYPE_2__ m_kobj; int /*<<< orphan*/  m_cowblocks_work; int /*<<< orphan*/  m_eofblocks_work; int /*<<< orphan*/  m_reclaim_work; int /*<<< orphan*/  m_active_trans; int /*<<< orphan*/  m_growlock; int /*<<< orphan*/  m_perag_lock; int /*<<< orphan*/  m_perag_tree; int /*<<< orphan*/  m_agirotor_lock; int /*<<< orphan*/  m_sb_lock; struct super_block* m_super; } ;
struct super_block {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INIT_RADIX_TREE (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct xfs_mount* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xfs_cowblocks_worker ; 
 int /*<<< orphan*/  xfs_eofblocks_worker ; 
 int /*<<< orphan*/  xfs_kset ; 
 int /*<<< orphan*/  xfs_reclaim_worker ; 

__attribute__((used)) static struct xfs_mount *
xfs_mount_alloc(
	struct super_block	*sb)
{
	struct xfs_mount	*mp;

	mp = kzalloc(sizeof(struct xfs_mount), GFP_KERNEL);
	if (!mp)
		return NULL;

	mp->m_super = sb;
	spin_lock_init(&mp->m_sb_lock);
	spin_lock_init(&mp->m_agirotor_lock);
	INIT_RADIX_TREE(&mp->m_perag_tree, GFP_ATOMIC);
	spin_lock_init(&mp->m_perag_lock);
	mutex_init(&mp->m_growlock);
	atomic_set(&mp->m_active_trans, 0);
	INIT_DELAYED_WORK(&mp->m_reclaim_work, xfs_reclaim_worker);
	INIT_DELAYED_WORK(&mp->m_eofblocks_work, xfs_eofblocks_worker);
	INIT_DELAYED_WORK(&mp->m_cowblocks_work, xfs_cowblocks_worker);
	mp->m_kobj.kobject.kset = xfs_kset;
	/*
	 * We don't create the finobt per-ag space reservation until after log
	 * recovery, so we must set this to true so that an ifree transaction
	 * started during log recovery will not depend on space reservations
	 * for finobt expansion.
	 */
	mp->m_finobt_nores = true;
	return mp;
}