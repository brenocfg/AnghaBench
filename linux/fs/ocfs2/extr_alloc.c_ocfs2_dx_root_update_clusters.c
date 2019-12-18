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
typedef  int /*<<< orphan*/  u32 ;
struct ocfs2_extent_tree {struct ocfs2_dx_root_block* et_object; } ;
struct ocfs2_dx_root_block {int /*<<< orphan*/  dr_clusters; } ;

/* Variables and functions */
 int /*<<< orphan*/  le32_add_cpu (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ocfs2_dx_root_update_clusters(struct ocfs2_extent_tree *et,
					  u32 clusters)
{
	struct ocfs2_dx_root_block *dx_root = et->et_object;

	le32_add_cpu(&dx_root->dr_clusters, clusters);
}