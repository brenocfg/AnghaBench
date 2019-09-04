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
typedef  int u64 ;
struct wpan_dev {int /*<<< orphan*/  wpan_phy; scalar_t__ identifier; } ;
struct TYPE_2__ {scalar_t__ wpan_phy_idx; } ;

/* Variables and functions */
 TYPE_1__* wpan_phy_to_rdev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline u64 wpan_dev_id(struct wpan_dev *wpan_dev)
{
	return (u64)wpan_dev->identifier |
	       ((u64)wpan_phy_to_rdev(wpan_dev->wpan_phy)->wpan_phy_idx << 32);
}