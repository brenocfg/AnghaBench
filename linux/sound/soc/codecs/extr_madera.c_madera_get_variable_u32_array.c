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
struct device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*,char const*,int) ; 
 int device_property_count_u32 (struct device*,char const*) ; 
 int device_property_read_u32_array (struct device*,char const*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int madera_get_variable_u32_array(struct device *dev,
					 const char *propname,
					 u32 *dest, int n_max,
					 int multiple)
{
	int n, ret;

	n = device_property_count_u32(dev, propname);
	if (n < 0) {
		if (n == -EINVAL)
			return 0;	/* missing, ignore */

		dev_warn(dev, "%s malformed (%d)\n", propname, n);

		return n;
	} else if ((n % multiple) != 0) {
		dev_warn(dev, "%s not a multiple of %d entries\n",
			 propname, multiple);

		return -EINVAL;
	}

	if (n > n_max)
		n = n_max;

	ret = device_property_read_u32_array(dev, propname, dest, n);
	if (ret < 0)
		return ret;

	return n;
}