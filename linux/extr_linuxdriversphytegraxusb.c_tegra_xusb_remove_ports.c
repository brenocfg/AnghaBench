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
struct tegra_xusb_padctl {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  __tegra_xusb_remove_ports (struct tegra_xusb_padctl*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void tegra_xusb_remove_ports(struct tegra_xusb_padctl *padctl)
{
	mutex_lock(&padctl->lock);
	__tegra_xusb_remove_ports(padctl);
	mutex_unlock(&padctl->lock);
}