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
struct ocfs2_cow_context {int /*<<< orphan*/  inode; } ;

/* Variables and functions */
 int ocfs2_get_clusters (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int*) ; 

__attribute__((used)) static int ocfs2_di_get_clusters(struct ocfs2_cow_context *context,
				 u32 v_cluster, u32 *p_cluster,
				 u32 *num_clusters,
				 unsigned int *extent_flags)
{
	return ocfs2_get_clusters(context->inode, v_cluster, p_cluster,
				  num_clusters, extent_flags);
}