#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
struct xfs_iext_leaf {TYPE_1__* recs; } ;
struct TYPE_2__ {int lo; } ;

/* Variables and functions */
 int XFS_IEXT_STARTOFF_MASK ; 

__attribute__((used)) static inline uint64_t
xfs_iext_leaf_key(
	struct xfs_iext_leaf	*leaf,
	int			n)
{
	return leaf->recs[n].lo & XFS_IEXT_STARTOFF_MASK;
}