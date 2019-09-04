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
struct timing_entry {int /*<<< orphan*/  min; int /*<<< orphan*/  typ; int /*<<< orphan*/  max; } ;
struct property {int dummy; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 struct property* of_find_property (struct device_node const*,char const*,int*) ; 
 int of_property_read_u32 (struct device_node const*,char const*,int /*<<< orphan*/ *) ; 
 int of_property_read_u32_array (struct device_node const*,char const*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pr_err (char*,struct device_node const*,char const*) ; 

__attribute__((used)) static int parse_timing_property(const struct device_node *np, const char *name,
			  struct timing_entry *result)
{
	struct property *prop;
	int length, cells, ret;

	prop = of_find_property(np, name, &length);
	if (!prop) {
		pr_err("%pOF: could not find property %s\n", np, name);
		return -EINVAL;
	}

	cells = length / sizeof(u32);
	if (cells == 1) {
		ret = of_property_read_u32(np, name, &result->typ);
		result->min = result->typ;
		result->max = result->typ;
	} else if (cells == 3) {
		ret = of_property_read_u32_array(np, name, &result->min, cells);
	} else {
		pr_err("%pOF: illegal timing specification in %s\n", np, name);
		return -EINVAL;
	}

	return ret;
}