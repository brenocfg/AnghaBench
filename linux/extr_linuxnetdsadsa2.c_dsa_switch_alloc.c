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
struct dsa_switch {size_t num_ports; TYPE_1__* ports; struct device* dev; int /*<<< orphan*/ * bitmap; int /*<<< orphan*/  _bitmap; } ;
struct dsa_port {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_2__ {int index; struct dsa_switch* ds; } ;

/* Variables and functions */
 int /*<<< orphan*/  BITS_TO_LONGS (size_t) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/ * devm_kcalloc (struct device*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 struct dsa_switch* devm_kzalloc (struct device*,size_t,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

struct dsa_switch *dsa_switch_alloc(struct device *dev, size_t n)
{
	size_t size = sizeof(struct dsa_switch) + n * sizeof(struct dsa_port);
	struct dsa_switch *ds;
	int i;

	ds = devm_kzalloc(dev, size, GFP_KERNEL);
	if (!ds)
		return NULL;

	/* We avoid allocating memory outside dsa_switch
	 * if it is not needed.
	 */
	if (n <= sizeof(ds->_bitmap) * 8) {
		ds->bitmap = &ds->_bitmap;
	} else {
		ds->bitmap = devm_kcalloc(dev,
					  BITS_TO_LONGS(n),
					  sizeof(unsigned long),
					  GFP_KERNEL);
		if (unlikely(!ds->bitmap))
			return NULL;
	}

	ds->dev = dev;
	ds->num_ports = n;

	for (i = 0; i < ds->num_ports; ++i) {
		ds->ports[i].index = i;
		ds->ports[i].ds = ds;
	}

	return ds;
}