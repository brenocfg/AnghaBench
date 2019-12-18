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
typedef  scalar_t__ u32 ;
struct ocfs2_extent_rec {int /*<<< orphan*/  e_cpos; int /*<<< orphan*/  e_leaf_clusters; } ;

/* Variables and functions */
 scalar_t__ le16_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ocfs2_extents_adjacent(struct ocfs2_extent_rec *left,
				  struct ocfs2_extent_rec *right)
{
	u32 left_range;

	left_range = le32_to_cpu(left->e_cpos) +
		le16_to_cpu(left->e_leaf_clusters);

	return (left_range == le32_to_cpu(right->e_cpos));
}