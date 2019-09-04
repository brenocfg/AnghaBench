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
struct regulator_init_data {int num_consumer_supplies; int /*<<< orphan*/ * consumer_supplies; } ;
struct regulator_desc {int dummy; } ;
struct regulator_config {TYPE_1__* dev; struct device_node* of_node; struct arizona_ldo1* driver_data; } ;
struct device_node {int dummy; } ;
struct arizona_ldo1_pdata {struct regulator_init_data* init_data; } ;
struct arizona_ldo1 {int /*<<< orphan*/  supply; } ;
struct TYPE_2__ {struct device_node* of_node; } ;

/* Variables and functions */
 struct device_node* of_get_child_by_name (struct device_node*,char*) ; 
 struct regulator_init_data* of_get_regulator_init_data (TYPE_1__*,struct device_node*,struct regulator_desc const*) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 struct device_node* of_parse_phandle (struct device_node*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int arizona_ldo1_of_get_pdata(struct arizona_ldo1_pdata *pdata,
				     struct regulator_config *config,
				     const struct regulator_desc *desc,
				     bool *external_dcvdd)
{
	struct arizona_ldo1 *ldo1 = config->driver_data;
	struct device_node *np = config->dev->of_node;
	struct device_node *init_node, *dcvdd_node;
	struct regulator_init_data *init_data;

	init_node = of_get_child_by_name(np, "ldo1");
	dcvdd_node = of_parse_phandle(np, "DCVDD-supply", 0);

	if (init_node) {
		config->of_node = init_node;

		init_data = of_get_regulator_init_data(config->dev, init_node,
						       desc);
		if (init_data) {
			init_data->consumer_supplies = &ldo1->supply;
			init_data->num_consumer_supplies = 1;

			if (dcvdd_node && dcvdd_node != init_node)
				*external_dcvdd = true;

			pdata->init_data = init_data;
		}
	} else if (dcvdd_node) {
		*external_dcvdd = true;
	}

	of_node_put(dcvdd_node);

	return 0;
}