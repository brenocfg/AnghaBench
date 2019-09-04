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
typedef  int /*<<< orphan*/  uint64_t ;
struct xfs_owner_info {scalar_t__ oi_flags; scalar_t__ oi_offset; int /*<<< orphan*/  oi_owner; } ;

/* Variables and functions */

__attribute__((used)) static inline void
xfs_rmap_ag_owner(
	struct xfs_owner_info	*oi,
	uint64_t		owner)
{
	oi->oi_owner = owner;
	oi->oi_offset = 0;
	oi->oi_flags = 0;
}