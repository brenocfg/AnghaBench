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
struct xfs_ifork {int if_height; } ;

/* Variables and functions */
 int RECS_PER_LEAF ; 
 int xfs_iext_count (struct xfs_ifork*) ; 

__attribute__((used)) static inline int xfs_iext_max_recs(struct xfs_ifork *ifp)
{
	if (ifp->if_height == 1)
		return xfs_iext_count(ifp);
	return RECS_PER_LEAF;
}