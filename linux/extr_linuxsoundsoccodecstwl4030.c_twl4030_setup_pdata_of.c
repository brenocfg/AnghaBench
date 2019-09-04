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
struct twl4030_codec_data {int digimic_delay; int ramp_delay_value; int offset_cncl_path; int hs_extmute; int /*<<< orphan*/  hs_extmute_gpio; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 scalar_t__ gpio_is_valid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_get_named_gpio (struct device_node*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_property_read_u32 (struct device_node*,char*,int*) ; 

__attribute__((used)) static void twl4030_setup_pdata_of(struct twl4030_codec_data *pdata,
				   struct device_node *node)
{
	int value;

	of_property_read_u32(node, "ti,digimic_delay",
			     &pdata->digimic_delay);
	of_property_read_u32(node, "ti,ramp_delay_value",
			     &pdata->ramp_delay_value);
	of_property_read_u32(node, "ti,offset_cncl_path",
			     &pdata->offset_cncl_path);
	if (!of_property_read_u32(node, "ti,hs_extmute", &value))
		pdata->hs_extmute = value;

	pdata->hs_extmute_gpio = of_get_named_gpio(node,
						   "ti,hs_extmute_gpio", 0);
	if (gpio_is_valid(pdata->hs_extmute_gpio))
		pdata->hs_extmute = 1;
}