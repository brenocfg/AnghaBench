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
struct ltq_rcu_usb2_priv {int /*<<< orphan*/  phy_gate_clk; int /*<<< orphan*/  phy_reset; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 struct ltq_rcu_usb2_priv* phy_get_drvdata (struct phy*) ; 
 int /*<<< orphan*/  reset_control_assert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ltq_rcu_usb2_phy_power_off(struct phy *phy)
{
	struct ltq_rcu_usb2_priv *priv = phy_get_drvdata(phy);

	reset_control_assert(priv->phy_reset);

	clk_disable_unprepare(priv->phy_gate_clk);

	return 0;
}