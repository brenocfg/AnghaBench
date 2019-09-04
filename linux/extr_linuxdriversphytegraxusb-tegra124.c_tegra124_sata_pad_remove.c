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
struct tegra_xusb_sata_pad {int dummy; } ;
struct tegra_xusb_pad {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct tegra_xusb_sata_pad*) ; 
 struct tegra_xusb_sata_pad* to_sata_pad (struct tegra_xusb_pad*) ; 

__attribute__((used)) static void tegra124_sata_pad_remove(struct tegra_xusb_pad *pad)
{
	struct tegra_xusb_sata_pad *sata = to_sata_pad(pad);

	kfree(sata);
}