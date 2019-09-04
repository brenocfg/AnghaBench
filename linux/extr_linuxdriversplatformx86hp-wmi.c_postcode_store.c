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
typedef  scalar_t__ u32 ;
typedef  int /*<<< orphan*/  tmp ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  HPWMI_POSTCODEERROR_QUERY ; 
 int /*<<< orphan*/  HPWMI_WRITE ; 
 int hp_wmi_perform_query (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,int,int) ; 
 int kstrtoul (char const*,int,unsigned long*) ; 

__attribute__((used)) static ssize_t postcode_store(struct device *dev, struct device_attribute *attr,
			      const char *buf, size_t count)
{
	long unsigned int tmp2;
	int ret;
	u32 tmp;

	ret = kstrtoul(buf, 10, &tmp2);
	if (!ret && tmp2 != 1)
		ret = -EINVAL;
	if (ret)
		goto out;

	/* Clear the POST error code. It is kept until until cleared. */
	tmp = (u32) tmp2;
	ret = hp_wmi_perform_query(HPWMI_POSTCODEERROR_QUERY, HPWMI_WRITE, &tmp,
				       sizeof(tmp), sizeof(tmp));

out:
	if (ret)
		return ret < 0 ? ret : -EINVAL;

	return count;
}