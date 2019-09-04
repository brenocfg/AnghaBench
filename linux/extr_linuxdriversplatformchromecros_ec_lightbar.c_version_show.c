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
typedef  int /*<<< orphan*/  uint32_t ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct cros_ec_dev {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  get_lightbar_version (struct cros_ec_dev*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int lb_throttle () ; 
 int scnprintf (char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct cros_ec_dev* to_cros_ec_dev (struct device*) ; 

__attribute__((used)) static ssize_t version_show(struct device *dev,
			    struct device_attribute *attr, char *buf)
{
	uint32_t version = 0, flags = 0;
	struct cros_ec_dev *ec = to_cros_ec_dev(dev);
	int ret;

	ret = lb_throttle();
	if (ret)
		return ret;

	/* This should always succeed, because we check during init. */
	if (!get_lightbar_version(ec, &version, &flags))
		return -EIO;

	return scnprintf(buf, PAGE_SIZE, "%d %d\n", version, flags);
}