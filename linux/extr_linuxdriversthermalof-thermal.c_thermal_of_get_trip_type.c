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
struct device_node {int dummy; } ;
typedef  enum thermal_trip_type { ____Placeholder_thermal_trip_type } thermal_trip_type ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int ENODEV ; 
 int of_property_read_string (struct device_node*,char*,char const**) ; 
 int /*<<< orphan*/  strcasecmp (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * trip_types ; 

__attribute__((used)) static int thermal_of_get_trip_type(struct device_node *np,
				    enum thermal_trip_type *type)
{
	const char *t;
	int err, i;

	err = of_property_read_string(np, "type", &t);
	if (err < 0)
		return err;

	for (i = 0; i < ARRAY_SIZE(trip_types); i++)
		if (!strcasecmp(t, trip_types[i])) {
			*type = i;
			return 0;
		}

	return -ENODEV;
}