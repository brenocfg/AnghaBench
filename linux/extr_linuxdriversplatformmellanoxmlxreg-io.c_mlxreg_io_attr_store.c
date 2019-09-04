#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct mlxreg_io_priv_data {TYPE_2__* pdev; TYPE_1__* pdata; } ;
struct mlxreg_core_data {int /*<<< orphan*/  reg; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;
struct TYPE_6__ {int index; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  regmap; struct mlxreg_core_data* data; } ;

/* Variables and functions */
 int EINVAL ; 
 size_t MLXREG_IO_ATT_SIZE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 struct mlxreg_io_priv_data* dev_get_drvdata (struct device*) ; 
 int kstrtou32 (char const*,size_t,int /*<<< orphan*/ *) ; 
 int mlxreg_io_get_reg (int /*<<< orphan*/ ,struct mlxreg_core_data*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__* to_sensor_dev_attr (struct device_attribute*) ; 

__attribute__((used)) static ssize_t
mlxreg_io_attr_store(struct device *dev, struct device_attribute *attr,
		     const char *buf, size_t len)
{
	struct mlxreg_io_priv_data *priv = dev_get_drvdata(dev);
	int index = to_sensor_dev_attr(attr)->index;
	struct mlxreg_core_data *data = priv->pdata->data + index;
	u32 input_val, regval;
	int ret;

	if (len > MLXREG_IO_ATT_SIZE)
		return -EINVAL;

	/* Convert buffer to input value. */
	ret = kstrtou32(buf, len, &input_val);
	if (ret)
		return ret;

	ret = mlxreg_io_get_reg(priv->pdata->regmap, data, input_val, false,
				&regval);
	if (ret)
		goto access_error;

	ret = regmap_write(priv->pdata->regmap, data->reg, regval);
	if (ret)
		goto access_error;

	return len;

access_error:
	dev_err(&priv->pdev->dev, "Bus access error\n");
	return ret;
}