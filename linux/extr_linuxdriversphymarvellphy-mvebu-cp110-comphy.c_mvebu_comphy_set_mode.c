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
struct phy {int dummy; } ;
struct mvebu_comphy_lane {int mode; int /*<<< orphan*/  port; int /*<<< orphan*/  id; } ;
typedef  enum phy_mode { ____Placeholder_phy_mode } phy_mode ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ mvebu_comphy_get_mux (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct mvebu_comphy_lane* phy_get_drvdata (struct phy*) ; 

__attribute__((used)) static int mvebu_comphy_set_mode(struct phy *phy, enum phy_mode mode)
{
	struct mvebu_comphy_lane *lane = phy_get_drvdata(phy);

	if (mvebu_comphy_get_mux(lane->id, lane->port, mode) < 0)
		return -EINVAL;

	lane->mode = mode;
	return 0;
}