#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  void* u32 ;
struct TYPE_3__ {struct device_node* of_node; } ;
struct i2c_client {TYPE_1__ dev; } ;
struct device_node {int dummy; } ;
struct bq24735_platform {int /*<<< orphan*/  ext_control; void* input_current; void* charge_voltage; void* charge_current; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*) ; 
 struct bq24735_platform* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_property_read_bool (struct device_node*,char*) ; 
 int of_property_read_u32 (struct device_node*,char*,void**) ; 

__attribute__((used)) static struct bq24735_platform *bq24735_parse_dt_data(struct i2c_client *client)
{
	struct bq24735_platform *pdata;
	struct device_node *np = client->dev.of_node;
	u32 val;
	int ret;

	pdata = devm_kzalloc(&client->dev, sizeof(*pdata), GFP_KERNEL);
	if (!pdata) {
		dev_err(&client->dev,
			"Memory alloc for bq24735 pdata failed\n");
		return NULL;
	}

	ret = of_property_read_u32(np, "ti,charge-current", &val);
	if (!ret)
		pdata->charge_current = val;

	ret = of_property_read_u32(np, "ti,charge-voltage", &val);
	if (!ret)
		pdata->charge_voltage = val;

	ret = of_property_read_u32(np, "ti,input-current", &val);
	if (!ret)
		pdata->input_current = val;

	pdata->ext_control = of_property_read_bool(np, "ti,external-control");

	return pdata;
}