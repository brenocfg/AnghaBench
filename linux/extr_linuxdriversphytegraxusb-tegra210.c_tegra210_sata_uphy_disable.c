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
struct tegra_xusb_sata_pad {scalar_t__ enable; int /*<<< orphan*/  pll; int /*<<< orphan*/  rst; } ;
struct tegra_xusb_padctl {int /*<<< orphan*/  lock; int /*<<< orphan*/  sata; } ;

/* Variables and functions */
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reset_control_assert (int /*<<< orphan*/ ) ; 
 struct tegra_xusb_sata_pad* to_sata_pad (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tegra210_sata_uphy_disable(struct tegra_xusb_padctl *padctl)
{
	struct tegra_xusb_sata_pad *sata = to_sata_pad(padctl->sata);

	mutex_lock(&padctl->lock);

	if (WARN_ON(sata->enable == 0))
		goto unlock;

	if (--sata->enable > 0)
		goto unlock;

	reset_control_assert(sata->rst);
	clk_disable_unprepare(sata->pll);

unlock:
	mutex_unlock(&padctl->lock);
}