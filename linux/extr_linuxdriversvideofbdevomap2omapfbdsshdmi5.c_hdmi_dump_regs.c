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
struct seq_file {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  core; int /*<<< orphan*/  phy; int /*<<< orphan*/  pll; int /*<<< orphan*/  wp; } ;

/* Variables and functions */
 TYPE_1__ hdmi ; 
 int /*<<< orphan*/  hdmi5_core_dump (int /*<<< orphan*/ *,struct seq_file*) ; 
 int /*<<< orphan*/  hdmi_phy_dump (int /*<<< orphan*/ *,struct seq_file*) ; 
 int /*<<< orphan*/  hdmi_pll_dump (int /*<<< orphan*/ *,struct seq_file*) ; 
 scalar_t__ hdmi_runtime_get () ; 
 int /*<<< orphan*/  hdmi_runtime_put () ; 
 int /*<<< orphan*/  hdmi_wp_dump (int /*<<< orphan*/ *,struct seq_file*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hdmi_dump_regs(struct seq_file *s)
{
	mutex_lock(&hdmi.lock);

	if (hdmi_runtime_get()) {
		mutex_unlock(&hdmi.lock);
		return;
	}

	hdmi_wp_dump(&hdmi.wp, s);
	hdmi_pll_dump(&hdmi.pll, s);
	hdmi_phy_dump(&hdmi.phy, s);
	hdmi5_core_dump(&hdmi.core, s);

	hdmi_runtime_put();
	mutex_unlock(&hdmi.lock);
}