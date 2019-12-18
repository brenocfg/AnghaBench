#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned long u32 ;
struct ag71xx_mdio {TYPE_2__* mii_bus; TYPE_1__* pdata; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {unsigned long ref_clock; unsigned long mdio_clock; scalar_t__ is_ar7240; scalar_t__ is_ar934x; scalar_t__ is_ar9330; } ;

/* Variables and functions */
 int ARRAY_SIZE (unsigned long*) ; 
 int EINVAL ; 
 int ENOENT ; 
 unsigned long* ar71xx_mdio_div_table ; 
 unsigned long* ar7240_mdio_div_table ; 
 unsigned long* ar933x_mdio_div_table ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,unsigned long,unsigned long) ; 

__attribute__((used)) static int ag71xx_mdio_get_divider(struct ag71xx_mdio *am, u32 *div)
{
	unsigned long ref_clock, mdio_clock;
	const u32 *table;
	int ndivs;
	int i;

	ref_clock = am->pdata->ref_clock;
	mdio_clock = am->pdata->mdio_clock;

	if (!ref_clock || !mdio_clock)
		return -EINVAL;

	if (am->pdata->is_ar9330 || am->pdata->is_ar934x) {
		table = ar933x_mdio_div_table;
		ndivs = ARRAY_SIZE(ar933x_mdio_div_table);
	} else if (am->pdata->is_ar7240) {
		table = ar7240_mdio_div_table;
		ndivs = ARRAY_SIZE(ar7240_mdio_div_table);
	} else {
		table = ar71xx_mdio_div_table;
		ndivs = ARRAY_SIZE(ar71xx_mdio_div_table);
	}

	for (i = 0; i < ndivs; i++) {
		unsigned long t;

		t = ref_clock / table[i];
		if (t <= mdio_clock) {
			*div = i;
			return 0;
		}
	}

	dev_err(&am->mii_bus->dev, "no divider found for %lu/%lu\n",
		ref_clock, mdio_clock);
	return -ENOENT;
}