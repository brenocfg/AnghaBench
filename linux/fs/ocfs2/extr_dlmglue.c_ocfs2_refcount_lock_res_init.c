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
typedef  int /*<<< orphan*/  u64 ;
struct ocfs2_super {int dummy; } ;
struct ocfs2_lock_res {int /*<<< orphan*/  l_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  OCFS2_LOCK_TYPE_REFCOUNT ; 
 int /*<<< orphan*/  ocfs2_build_lock_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_lock_res_init_common (struct ocfs2_super*,struct ocfs2_lock_res*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct ocfs2_super*) ; 
 int /*<<< orphan*/  ocfs2_lock_res_init_once (struct ocfs2_lock_res*) ; 
 int /*<<< orphan*/  ocfs2_refcount_block_lops ; 

void ocfs2_refcount_lock_res_init(struct ocfs2_lock_res *lockres,
				  struct ocfs2_super *osb, u64 ref_blkno,
				  unsigned int generation)
{
	ocfs2_lock_res_init_once(lockres);
	ocfs2_build_lock_name(OCFS2_LOCK_TYPE_REFCOUNT, ref_blkno,
			      generation, lockres->l_name);
	ocfs2_lock_res_init_common(osb, lockres, OCFS2_LOCK_TYPE_REFCOUNT,
				   &ocfs2_refcount_block_lops, osb);
}