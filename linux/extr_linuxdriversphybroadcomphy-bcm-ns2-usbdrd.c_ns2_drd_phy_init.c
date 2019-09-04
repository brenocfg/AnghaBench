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
struct phy {int dummy; } ;
struct ns2_phy_driver {scalar_t__ icfgdrd_regs; } ;
struct ns2_phy_data {scalar_t__ new_state; struct ns2_phy_driver* driver; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRD_DEVICE_MODE ; 
 int /*<<< orphan*/  DRD_HOST_MODE ; 
 scalar_t__ EVT_HOST ; 
 scalar_t__ ICFG_FSM_CTRL ; 
 struct ns2_phy_data* phy_get_drvdata (struct phy*) ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int ns2_drd_phy_init(struct phy *phy)
{
	struct ns2_phy_data *data = phy_get_drvdata(phy);
	struct ns2_phy_driver *driver = data->driver;
	u32 val;

	val = readl(driver->icfgdrd_regs + ICFG_FSM_CTRL);

	if (data->new_state == EVT_HOST) {
		val &= ~DRD_DEVICE_MODE;
		val |= DRD_HOST_MODE;
	} else {
		val &= ~DRD_HOST_MODE;
		val |= DRD_DEVICE_MODE;
	}
	writel(val, driver->icfgdrd_regs + ICFG_FSM_CTRL);

	return 0;
}