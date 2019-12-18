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
struct ocfs2_inode_info {int /*<<< orphan*/  ip_lock; int /*<<< orphan*/  ip_clusters; } ;
struct ocfs2_extent_tree {struct ocfs2_dinode* et_object; int /*<<< orphan*/  et_ci; } ;
struct ocfs2_dinode {int /*<<< orphan*/  i_clusters; } ;

/* Variables and functions */
 struct ocfs2_inode_info* cache_info_to_inode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32_add_cpu (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ocfs2_dinode_update_clusters(struct ocfs2_extent_tree *et,
					 u32 clusters)
{
	struct ocfs2_inode_info *oi = cache_info_to_inode(et->et_ci);
	struct ocfs2_dinode *di = et->et_object;

	le32_add_cpu(&di->i_clusters, clusters);
	spin_lock(&oi->ip_lock);
	oi->ip_clusters = le32_to_cpu(di->i_clusters);
	spin_unlock(&oi->ip_lock);
}