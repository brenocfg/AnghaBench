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
struct dsa_switch {TYPE_1__* dev; } ;
struct dsa_chip_data {int dummy; } ;
struct device_node {int dummy; } ;
struct TYPE_2__ {struct device_node* of_node; struct dsa_chip_data* platform_data; } ;

/* Variables and functions */
 int ENODEV ; 
 int dsa_switch_add (struct dsa_switch*) ; 
 int dsa_switch_parse (struct dsa_switch*,struct dsa_chip_data*) ; 
 int dsa_switch_parse_of (struct dsa_switch*,struct device_node*) ; 

__attribute__((used)) static int dsa_switch_probe(struct dsa_switch *ds)
{
	struct dsa_chip_data *pdata = ds->dev->platform_data;
	struct device_node *np = ds->dev->of_node;
	int err;

	if (np)
		err = dsa_switch_parse_of(ds, np);
	else if (pdata)
		err = dsa_switch_parse(ds, pdata);
	else
		err = -ENODEV;

	if (err)
		return err;

	return dsa_switch_add(ds);
}