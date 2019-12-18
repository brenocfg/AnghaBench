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
struct ocfs2_super {int dummy; } ;
struct ocfs2_alloc_context {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOC_NEW_GROUP ; 
 int ocfs2_reserve_clusters_with_limit (struct ocfs2_super*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ocfs2_alloc_context**) ; 

int ocfs2_reserve_clusters(struct ocfs2_super *osb,
			   u32 bits_wanted,
			   struct ocfs2_alloc_context **ac)
{
	return ocfs2_reserve_clusters_with_limit(osb, bits_wanted, 0,
						 ALLOC_NEW_GROUP, ac);
}