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
struct radix_tree_root {int dummy; } ;
struct xfs_quotainfo {struct radix_tree_root qi_pquota_tree; struct radix_tree_root qi_gquota_tree; struct radix_tree_root qi_uquota_tree; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
#define  XFS_DQ_GROUP 130 
#define  XFS_DQ_PROJ 129 
#define  XFS_DQ_USER 128 

__attribute__((used)) static inline struct radix_tree_root *
xfs_dquot_tree(
	struct xfs_quotainfo	*qi,
	int			type)
{
	switch (type) {
	case XFS_DQ_USER:
		return &qi->qi_uquota_tree;
	case XFS_DQ_GROUP:
		return &qi->qi_gquota_tree;
	case XFS_DQ_PROJ:
		return &qi->qi_pquota_tree;
	default:
		ASSERT(0);
	}
	return NULL;
}