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
struct xfs_phys_extent {int pe_flags; } ;
typedef  enum xfs_refcount_intent_type { ____Placeholder_xfs_refcount_intent_type } xfs_refcount_intent_type ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
#define  XFS_REFCOUNT_ALLOC_COW 131 
#define  XFS_REFCOUNT_DECREASE 130 
#define  XFS_REFCOUNT_FREE_COW 129 
#define  XFS_REFCOUNT_INCREASE 128 

__attribute__((used)) static void
xfs_trans_set_refcount_flags(
	struct xfs_phys_extent		*refc,
	enum xfs_refcount_intent_type	type)
{
	refc->pe_flags = 0;
	switch (type) {
	case XFS_REFCOUNT_INCREASE:
	case XFS_REFCOUNT_DECREASE:
	case XFS_REFCOUNT_ALLOC_COW:
	case XFS_REFCOUNT_FREE_COW:
		refc->pe_flags |= type;
		break;
	default:
		ASSERT(0);
	}
}