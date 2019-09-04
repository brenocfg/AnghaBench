#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ideapad_private {TYPE_1__* adev; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;
struct TYPE_2__ {int /*<<< orphan*/  handle; } ;

/* Variables and functions */
 size_t EINVAL ; 
 size_t EIO ; 
 int /*<<< orphan*/  VPCCMD_W_FAN ; 
 struct ideapad_private* dev_get_drvdata (struct device*) ; 
 int sscanf (char const*,char*,int*) ; 
 int write_ec_cmd (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static ssize_t store_ideapad_fan(struct device *dev,
				 struct device_attribute *attr,
				 const char *buf, size_t count)
{
	int ret, state;
	struct ideapad_private *priv = dev_get_drvdata(dev);

	if (!count)
		return 0;
	if (sscanf(buf, "%i", &state) != 1)
		return -EINVAL;
	if (state < 0 || state > 4 || state == 3)
		return -EINVAL;
	ret = write_ec_cmd(priv->adev->handle, VPCCMD_W_FAN, state);
	if (ret < 0)
		return -EIO;
	return count;
}