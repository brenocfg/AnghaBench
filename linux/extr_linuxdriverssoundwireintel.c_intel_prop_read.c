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
struct TYPE_2__ {int num_freq; int err_threshold; int /*<<< orphan*/  max_freq; int /*<<< orphan*/ * freq; } ;
struct sdw_bus {TYPE_1__ prop; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/ * devm_kcalloc (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdw_master_read_prop (struct sdw_bus*) ; 

__attribute__((used)) static int intel_prop_read(struct sdw_bus *bus)
{
	/* Initialize with default handler to read all DisCo properties */
	sdw_master_read_prop(bus);

	/* BIOS is not giving some values correctly. So, lets override them */
	bus->prop.num_freq = 1;
	bus->prop.freq = devm_kcalloc(bus->dev, sizeof(*bus->prop.freq),
					bus->prop.num_freq, GFP_KERNEL);
	if (!bus->prop.freq)
		return -ENOMEM;

	bus->prop.freq[0] = bus->prop.max_freq;
	bus->prop.err_threshold = 5;

	return 0;
}