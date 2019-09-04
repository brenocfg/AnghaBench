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
typedef  int /*<<< orphan*/  u64 ;
typedef  int u32 ;
struct device_node {int dummy; } ;
typedef  int /*<<< orphan*/  __be64 ;

/* Variables and functions */
 scalar_t__ IS_ERR (int /*<<< orphan*/  const*) ; 
 int PTR_ERR (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  be64_to_cpup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * of_find_property_value_of_size (struct device_node const*,char const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int of_property_read_u64_index(const struct device_node *np,
				       const char *propname,
				       u32 index, u64 *out_value)
{
	const u64 *val = of_find_property_value_of_size(np, propname,
					((index + 1) * sizeof(*out_value)),
					0, NULL);

	if (IS_ERR(val))
		return PTR_ERR(val);

	*out_value = be64_to_cpup(((__be64 *)val) + index);
	return 0;
}