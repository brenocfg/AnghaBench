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
struct pn544_i2c_phy {int en_polarity; int run_mode; int /*<<< orphan*/  gpiod_en; int /*<<< orphan*/  gpiod_fw; } ;

/* Variables and functions */
 int PN544_FW_MODE ; 
 int /*<<< orphan*/  gpiod_set_value_cansleep (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static void pn544_hci_i2c_enable_mode(struct pn544_i2c_phy *phy, int run_mode)
{
	gpiod_set_value_cansleep(phy->gpiod_fw, run_mode == PN544_FW_MODE ? 1 : 0);
	gpiod_set_value_cansleep(phy->gpiod_en, phy->en_polarity);
	usleep_range(10000, 15000);

	phy->run_mode = run_mode;
}