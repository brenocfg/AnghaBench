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
typedef  void* u32 ;
struct TYPE_2__ {struct device_node* of_node; } ;
struct i2c_client {TYPE_1__ dev; } ;
struct device_node {int dummy; } ;
struct cs42l56_platform_data {int ain1a_ref_cfg; int ain2a_ref_cfg; int ain1b_ref_cfg; int ain2b_ref_cfg; int /*<<< orphan*/  gpio_nreset; void* hpfb_freq; void* hpfa_freq; void* adaptive_pwr; void* chgfreq; void* micbias_lvl; } ;

/* Variables and functions */
 int /*<<< orphan*/  of_get_named_gpio (struct device_node*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ of_property_read_bool (struct device_node*,char*) ; 
 scalar_t__ of_property_read_u32 (struct device_node*,char*,void**) ; 

__attribute__((used)) static int cs42l56_handle_of_data(struct i2c_client *i2c_client,
				    struct cs42l56_platform_data *pdata)
{
	struct device_node *np = i2c_client->dev.of_node;
	u32 val32;

	if (of_property_read_bool(np, "cirrus,ain1a-reference-cfg"))
		pdata->ain1a_ref_cfg = true;

	if (of_property_read_bool(np, "cirrus,ain2a-reference-cfg"))
		pdata->ain2a_ref_cfg = true;

	if (of_property_read_bool(np, "cirrus,ain1b-reference-cfg"))
		pdata->ain1b_ref_cfg = true;

	if (of_property_read_bool(np, "cirrus,ain2b-reference-cfg"))
		pdata->ain2b_ref_cfg = true;

	if (of_property_read_u32(np, "cirrus,micbias-lvl", &val32) >= 0)
		pdata->micbias_lvl = val32;

	if (of_property_read_u32(np, "cirrus,chgfreq-divisor", &val32) >= 0)
		pdata->chgfreq = val32;

	if (of_property_read_u32(np, "cirrus,adaptive-pwr-cfg", &val32) >= 0)
		pdata->adaptive_pwr = val32;

	if (of_property_read_u32(np, "cirrus,hpf-left-freq", &val32) >= 0)
		pdata->hpfa_freq = val32;

	if (of_property_read_u32(np, "cirrus,hpf-left-freq", &val32) >= 0)
		pdata->hpfb_freq = val32;

	pdata->gpio_nreset = of_get_named_gpio(np, "cirrus,gpio-nreset", 0);

	return 0;
}