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
struct TYPE_2__ {unsigned int num; } ;
struct ec_params_lightbar {TYPE_1__ set_brightness; int /*<<< orphan*/  cmd; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct cros_ec_dev {int /*<<< orphan*/  ec_dev; } ;
struct cros_ec_command {scalar_t__ result; scalar_t__ data; } ;
typedef  int ssize_t ;

/* Variables and functions */
 scalar_t__ EC_RES_SUCCESS ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  LIGHTBAR_CMD_SET_BRIGHTNESS ; 
 struct cros_ec_command* alloc_lightbar_cmd_msg (struct cros_ec_dev*) ; 
 int cros_ec_cmd_xfer (int /*<<< orphan*/ ,struct cros_ec_command*) ; 
 int /*<<< orphan*/  kfree (struct cros_ec_command*) ; 
 scalar_t__ kstrtouint (char const*,int /*<<< orphan*/ ,unsigned int*) ; 
 int lb_throttle () ; 
 struct cros_ec_dev* to_cros_ec_dev (struct device*) ; 

__attribute__((used)) static ssize_t brightness_store(struct device *dev,
				struct device_attribute *attr,
				const char *buf, size_t count)
{
	struct ec_params_lightbar *param;
	struct cros_ec_command *msg;
	int ret;
	unsigned int val;
	struct cros_ec_dev *ec = to_cros_ec_dev(dev);

	if (kstrtouint(buf, 0, &val))
		return -EINVAL;

	msg = alloc_lightbar_cmd_msg(ec);
	if (!msg)
		return -ENOMEM;

	param = (struct ec_params_lightbar *)msg->data;
	param->cmd = LIGHTBAR_CMD_SET_BRIGHTNESS;
	param->set_brightness.num = val;
	ret = lb_throttle();
	if (ret)
		goto exit;

	ret = cros_ec_cmd_xfer(ec->ec_dev, msg);
	if (ret < 0)
		goto exit;

	if (msg->result != EC_RES_SUCCESS) {
		ret = -EINVAL;
		goto exit;
	}

	ret = count;
exit:
	kfree(msg);
	return ret;
}