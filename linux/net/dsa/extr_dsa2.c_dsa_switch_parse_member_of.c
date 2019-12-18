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
typedef  int /*<<< orphan*/  u32 ;
struct dsa_switch {int /*<<< orphan*/  dst; int /*<<< orphan*/  index; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSA_MAX_SWITCHES ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  dsa_tree_touch (int /*<<< orphan*/ ) ; 
 int of_property_read_variable_u32_array (struct device_node*,char*,int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static int dsa_switch_parse_member_of(struct dsa_switch *ds,
				      struct device_node *dn)
{
	u32 m[2] = { 0, 0 };
	int sz;

	/* Don't error out if this optional property isn't found */
	sz = of_property_read_variable_u32_array(dn, "dsa,member", m, 2, 2);
	if (sz < 0 && sz != -EINVAL)
		return sz;

	ds->index = m[1];
	if (ds->index >= DSA_MAX_SWITCHES)
		return -EINVAL;

	ds->dst = dsa_tree_touch(m[0]);
	if (!ds->dst)
		return -ENOMEM;

	return 0;
}