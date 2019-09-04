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
typedef  scalar_t__ z_erofs_vle_owned_workgrp_t ;
struct z_erofs_vle_workgroup {int /*<<< orphan*/ * compressed_pages; } ;
struct z_erofs_vle_work_builder {unsigned int compressed_deficit; struct z_erofs_vle_work* work; struct z_erofs_vle_workgroup* grp; int /*<<< orphan*/ * compressed_pages; int /*<<< orphan*/  role; int /*<<< orphan*/  vector; int /*<<< orphan*/  hosted; } ;
struct z_erofs_vle_work {int /*<<< orphan*/  vcnt; int /*<<< orphan*/  pagevec; } ;
struct super_block {int dummy; } ;
struct erofs_map_blocks {unsigned int m_la; int /*<<< orphan*/  m_llen; int /*<<< orphan*/  m_pa; } ;
typedef  int /*<<< orphan*/  erofs_blk_t ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_BUGON (int) ; 
 int /*<<< orphan*/  EAGAIN ; 
 int /*<<< orphan*/  EROFS_SB (struct super_block*) ; 
 struct z_erofs_vle_work* ERR_PTR (int /*<<< orphan*/ ) ; 
 int IS_ERR (struct z_erofs_vle_work*) ; 
 unsigned int PAGE_MASK ; 
 int PTR_ERR (struct z_erofs_vle_work*) ; 
 int /*<<< orphan*/  Z_EROFS_VLE_INLINE_PAGEVECS ; 
 scalar_t__ Z_EROFS_VLE_WORKGRP_NIL ; 
 scalar_t__ Z_EROFS_VLE_WORKGRP_TAIL_CLOSED ; 
 int /*<<< orphan*/  Z_EROFS_VLE_WORK_PRIMARY ; 
 int /*<<< orphan*/  __update_workgrp_llen (struct z_erofs_vle_workgroup*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  erofs_blknr (int /*<<< orphan*/ ) ; 
 int erofs_blkoff (int /*<<< orphan*/ ) ; 
 unsigned int erofs_clusterpages (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  z_erofs_pagevec_ctor_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct z_erofs_vle_work* z_erofs_vle_work_lookup (struct super_block*,int /*<<< orphan*/  const,unsigned int const,struct z_erofs_vle_workgroup**,int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ *) ; 
 struct z_erofs_vle_work* z_erofs_vle_work_register (struct super_block*,struct z_erofs_vle_workgroup**,struct erofs_map_blocks*,int /*<<< orphan*/  const,unsigned int const,int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int z_erofs_vle_work_iter_begin(struct z_erofs_vle_work_builder *builder,
				       struct super_block *sb,
				       struct erofs_map_blocks *map,
				       z_erofs_vle_owned_workgrp_t *owned_head)
{
	const unsigned clusterpages = erofs_clusterpages(EROFS_SB(sb));
	const erofs_blk_t index = erofs_blknr(map->m_pa);
	const unsigned pageofs = map->m_la & ~PAGE_MASK;
	struct z_erofs_vle_workgroup *grp;
	struct z_erofs_vle_work *work;

	DBG_BUGON(builder->work != NULL);

	/* must be Z_EROFS_WORK_TAIL or the next chained work */
	DBG_BUGON(*owned_head == Z_EROFS_VLE_WORKGRP_NIL);
	DBG_BUGON(*owned_head == Z_EROFS_VLE_WORKGRP_TAIL_CLOSED);

	DBG_BUGON(erofs_blkoff(map->m_pa));

repeat:
	work = z_erofs_vle_work_lookup(sb, index,
		pageofs, &grp, &builder->role, owned_head, &builder->hosted);
	if (work != NULL) {
		__update_workgrp_llen(grp, map->m_llen);
		goto got_it;
	}

	work = z_erofs_vle_work_register(sb, &grp, map, index, pageofs,
		&builder->role, owned_head, &builder->hosted);

	if (unlikely(work == ERR_PTR(-EAGAIN)))
		goto repeat;

	if (unlikely(IS_ERR(work)))
		return PTR_ERR(work);
got_it:
	z_erofs_pagevec_ctor_init(&builder->vector,
		Z_EROFS_VLE_INLINE_PAGEVECS, work->pagevec, work->vcnt);

	if (builder->role >= Z_EROFS_VLE_WORK_PRIMARY) {
		/* enable possibly in-place decompression */
		builder->compressed_pages = grp->compressed_pages;
		builder->compressed_deficit = clusterpages;
	} else {
		builder->compressed_pages = NULL;
		builder->compressed_deficit = 0;
	}

	builder->grp = grp;
	builder->work = work;
	return 0;
}