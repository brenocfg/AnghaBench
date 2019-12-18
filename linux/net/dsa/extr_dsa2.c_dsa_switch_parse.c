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
struct dsa_switch {int /*<<< orphan*/  dst; scalar_t__ index; struct dsa_chip_data* cd; } ;
struct dsa_chip_data {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int dsa_switch_parse_ports (struct dsa_switch*,struct dsa_chip_data*) ; 
 int /*<<< orphan*/  dsa_tree_touch (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dsa_switch_parse(struct dsa_switch *ds, struct dsa_chip_data *cd)
{
	ds->cd = cd;

	/* We don't support interconnected switches nor multiple trees via
	 * platform data, so this is the unique switch of the tree.
	 */
	ds->index = 0;
	ds->dst = dsa_tree_touch(0);
	if (!ds->dst)
		return -ENOMEM;

	return dsa_switch_parse_ports(ds, cd);
}