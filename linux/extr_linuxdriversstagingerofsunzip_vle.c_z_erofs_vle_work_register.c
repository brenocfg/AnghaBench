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
typedef  struct z_erofs_vle_workgroup* z_erofs_vle_owned_workgrp_t ;
struct TYPE_2__ {int /*<<< orphan*/  refcount; int /*<<< orphan*/  index; } ;
struct z_erofs_vle_workgroup {TYPE_1__ obj; int /*<<< orphan*/  next; int /*<<< orphan*/  llen; } ;
struct z_erofs_vle_work {unsigned int pageofs; int /*<<< orphan*/  lock; } ;
struct super_block {int dummy; } ;
struct erofs_map_blocks {int m_flags; int /*<<< orphan*/  m_llen; } ;
typedef  int /*<<< orphan*/  pgoff_t ;
typedef  enum z_erofs_vle_work_role { ____Placeholder_z_erofs_vle_work_role } z_erofs_vle_work_role ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_BUGON (int) ; 
 int /*<<< orphan*/  EAGAIN ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 int EROFS_MAP_ZIPPED ; 
 struct z_erofs_vle_work* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  WRITE_ONCE (int /*<<< orphan*/ ,struct z_erofs_vle_workgroup*) ; 
 int /*<<< orphan*/  Z_EROFS_VLE_WORKGRP_FMT_LZ4 ; 
 int /*<<< orphan*/  Z_EROFS_VLE_WORKGRP_FMT_PLAIN ; 
 int Z_EROFS_VLE_WORK_PRIMARY_FOLLOWED ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int erofs_register_workgroup (struct super_block*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct z_erofs_vle_workgroup*) ; 
 struct z_erofs_vle_workgroup* kmem_cache_zalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (struct z_erofs_vle_workgroup*) ; 
 struct z_erofs_vle_work* z_erofs_vle_grab_primary_work (struct z_erofs_vle_workgroup*) ; 
 int /*<<< orphan*/  z_erofs_vle_set_workgrp_fmt (struct z_erofs_vle_workgroup*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  z_erofs_workgroup_cachep ; 

__attribute__((used)) static struct z_erofs_vle_work *
z_erofs_vle_work_register(struct super_block *sb,
			  struct z_erofs_vle_workgroup **grp_ret,
			  struct erofs_map_blocks *map,
			  pgoff_t index, unsigned pageofs,
			  enum z_erofs_vle_work_role *role,
			  z_erofs_vle_owned_workgrp_t *owned_head,
			  bool *hosted)
{
	bool newgrp = false;
	struct z_erofs_vle_workgroup *grp = *grp_ret;
	struct z_erofs_vle_work *work;

	/* if multiref is disabled, grp should never be nullptr */
	if (unlikely(grp)) {
		DBG_BUGON(1);
		return ERR_PTR(-EINVAL);
	}

	/* no available workgroup, let's allocate one */
	grp = kmem_cache_zalloc(z_erofs_workgroup_cachep, GFP_NOFS);
	if (unlikely(grp == NULL))
		return ERR_PTR(-ENOMEM);

	grp->obj.index = index;
	grp->llen = map->m_llen;

	z_erofs_vle_set_workgrp_fmt(grp,
		(map->m_flags & EROFS_MAP_ZIPPED) ?
			Z_EROFS_VLE_WORKGRP_FMT_LZ4 :
			Z_EROFS_VLE_WORKGRP_FMT_PLAIN);
	atomic_set(&grp->obj.refcount, 1);

	/* new workgrps have been claimed as type 1 */
	WRITE_ONCE(grp->next, *owned_head);
	/* primary and followed work for all new workgrps */
	*role = Z_EROFS_VLE_WORK_PRIMARY_FOLLOWED;
	/* it should be submitted by ourselves */
	*hosted = true;

	newgrp = true;
	work = z_erofs_vle_grab_primary_work(grp);
	work->pageofs = pageofs;

	mutex_init(&work->lock);

	if (newgrp) {
		int err = erofs_register_workgroup(sb, &grp->obj, 0);

		if (err) {
			kmem_cache_free(z_erofs_workgroup_cachep, grp);
			return ERR_PTR(-EAGAIN);
		}
	}

	*owned_head = *grp_ret = grp;

	mutex_lock(&work->lock);
	return work;
}