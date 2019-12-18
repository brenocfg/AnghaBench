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
typedef  unsigned long u32 ;
struct device_node {int dummy; } ;
struct clk {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (unsigned long*) ; 
 int EINVAL ; 
 int ENOENT ; 
 scalar_t__ IS_ERR (struct clk*) ; 
 unsigned long* ar71xx_mdio_div_table ; 
 unsigned long* ar7240_mdio_div_table ; 
 unsigned long* ar933x_mdio_div_table ; 
 unsigned long clk_get_rate (struct clk*) ; 
 int /*<<< orphan*/  clk_put (struct clk*) ; 
 struct clk* of_clk_get (struct device_node*,int /*<<< orphan*/ ) ; 
 scalar_t__ of_device_is_compatible (struct device_node*,char*) ; 
 scalar_t__ of_property_read_bool (struct device_node*,char*) ; 
 scalar_t__ of_property_read_u32 (struct device_node*,char*,unsigned long*) ; 

__attribute__((used)) static int ag71xx_mdio_get_divider(struct device_node *np, u32 *div)
{
	struct clk *ref_clk = of_clk_get(np, 0);
	unsigned long ref_clock;
	u32 mdio_clock;
	const u32 *table;
	int ndivs, i;

	if (IS_ERR(ref_clk))
		return -EINVAL;

	ref_clock = clk_get_rate(ref_clk);
	clk_put(ref_clk);

	if(of_property_read_u32(np, "qca,mdio-max-frequency", &mdio_clock)) {
		if (of_property_read_bool(np, "builtin-switch"))
			mdio_clock = 5000000;
		else
			mdio_clock = 2000000;
	}

	if (of_device_is_compatible(np, "qca,ar9330-mdio") ||
		of_device_is_compatible(np, "qca,ar9340-mdio")) {
		table = ar933x_mdio_div_table;
		ndivs = ARRAY_SIZE(ar933x_mdio_div_table);
	} else if (of_device_is_compatible(np, "qca,ar7240-mdio")) {
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

	return -ENOENT;
}