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
struct phy_control {int /*<<< orphan*/  (* phy_wkup ) (struct phy_control*,int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct phy_control*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void phy_ctrl_wkup(struct phy_control *phy_ctrl, u32 id, bool on)
{
	phy_ctrl->phy_wkup(phy_ctrl, id, on);
}