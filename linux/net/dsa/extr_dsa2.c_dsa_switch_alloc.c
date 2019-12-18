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
struct dsa_switch {size_t num_ports; TYPE_1__* ports; struct device* dev; } ;
struct device {int dummy; } ;
struct TYPE_2__ {int index; struct dsa_switch* ds; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct dsa_switch* devm_kzalloc (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ports ; 
 int /*<<< orphan*/  struct_size (struct dsa_switch*,int /*<<< orphan*/ ,size_t) ; 

struct dsa_switch *dsa_switch_alloc(struct device *dev, size_t n)
{
	struct dsa_switch *ds;
	int i;

	ds = devm_kzalloc(dev, struct_size(ds, ports, n), GFP_KERNEL);
	if (!ds)
		return NULL;

	ds->dev = dev;
	ds->num_ports = n;

	for (i = 0; i < ds->num_ports; ++i) {
		ds->ports[i].index = i;
		ds->ports[i].ds = ds;
	}

	return ds;
}