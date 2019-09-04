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
struct xfs_owner_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  XFS_RMAP_OWN_NULL ; 
 int /*<<< orphan*/  xfs_rmap_ag_owner (struct xfs_owner_info*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
xfs_rmap_skip_owner_update(
	struct xfs_owner_info	*oi)
{
	xfs_rmap_ag_owner(oi, XFS_RMAP_OWN_NULL);
}