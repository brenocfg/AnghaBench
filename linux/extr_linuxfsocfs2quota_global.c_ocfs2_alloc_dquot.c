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
struct super_block {int dummy; } ;
struct dquot {int dummy; } ;
struct ocfs2_dquot {struct dquot dq_dquot; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_NOFS ; 
 struct ocfs2_dquot* kmem_cache_zalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_dquot_cachep ; 

__attribute__((used)) static struct dquot *ocfs2_alloc_dquot(struct super_block *sb, int type)
{
	struct ocfs2_dquot *dquot =
				kmem_cache_zalloc(ocfs2_dquot_cachep, GFP_NOFS);

	if (!dquot)
		return NULL;
	return &dquot->dq_dquot;
}