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
typedef  int /*<<< orphan*/  u32 ;
struct sunxi_priv_data {int /*<<< orphan*/  regmap_field; TYPE_1__* variant; } ;
struct TYPE_2__ {int /*<<< orphan*/  default_syscon_value; } ;

/* Variables and functions */
 int /*<<< orphan*/  regmap_field_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sun8i_dwmac_unset_syscon(struct sunxi_priv_data *gmac)
{
	u32 reg = gmac->variant->default_syscon_value;

	regmap_field_write(gmac->regmap_field, reg);
}