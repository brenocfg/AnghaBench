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
struct st21nfca_i2c_phy {scalar_t__ powered; int /*<<< orphan*/  gpiod_ena; } ;

/* Variables and functions */
 int /*<<< orphan*/  gpiod_set_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void st21nfca_hci_i2c_disable(void *phy_id)
{
	struct st21nfca_i2c_phy *phy = phy_id;

	gpiod_set_value(phy->gpiod_ena, 0);

	phy->powered = 0;
}