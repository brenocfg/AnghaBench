#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct vpfe_ext_subdev_info {scalar_t__ is_camera; int registered; int /*<<< orphan*/  module_name; int /*<<< orphan*/  grp_id; int /*<<< orphan*/  board_info; } ;
struct vpfe_device {int num_ext_subdevs; TYPE_1__** sd; int /*<<< orphan*/  v4l2_dev; struct vpfe_config* cfg; } ;
struct vpfe_config {unsigned int num_subdevs; scalar_t__ (* setup_input ) (int /*<<< orphan*/ ) ;struct vpfe_ext_subdev_info* sub_devs; } ;
struct v4l2_subdev {int dummy; } ;
struct i2c_adapter {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  grp_id; } ;

/* Variables and functions */
 int EFAULT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct i2c_adapter* i2c_get_adapter (int) ; 
 scalar_t__ interface ; 
 TYPE_1__** kcalloc (unsigned int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kzfree (TYPE_1__**) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ) ; 
 TYPE_1__* v4l2_i2c_new_subdev_board (int /*<<< orphan*/ *,struct i2c_adapter*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int register_i2c_devices(struct vpfe_device *vpfe_dev)
{
	struct vpfe_ext_subdev_info *sdinfo;
	struct vpfe_config *vpfe_cfg;
	struct i2c_adapter *i2c_adap;
	unsigned int num_subdevs;
	int ret;
	int i;
	int k;

	vpfe_cfg = vpfe_dev->cfg;
	i2c_adap = i2c_get_adapter(1);
	num_subdevs = vpfe_cfg->num_subdevs;
	vpfe_dev->sd =
		  kcalloc(num_subdevs, sizeof(struct v4l2_subdev *),
			  GFP_KERNEL);
	if (!vpfe_dev->sd)
		return -ENOMEM;

	for (i = 0, k = 0; i < num_subdevs; i++) {
		sdinfo = &vpfe_cfg->sub_devs[i];
		/*
		 * register subdevices based on interface setting. Currently
		 * tvp5146 and mt9p031 cannot co-exists due to i2c address
		 * conflicts. So only one of them is registered. Re-visit this
		 * once we have support for i2c switch handling in i2c driver
		 * framework
		 */
		if (interface == sdinfo->is_camera) {
			/* setup input path */
			if (vpfe_cfg->setup_input &&
				vpfe_cfg->setup_input(sdinfo->grp_id) < 0) {
				ret = -EFAULT;
				v4l2_info(&vpfe_dev->v4l2_dev,
					  "could not setup input for %s\n",
						sdinfo->module_name);
				goto probe_sd_out;
			}
			/* Load up the subdevice */
			vpfe_dev->sd[k] =
				v4l2_i2c_new_subdev_board(&vpfe_dev->v4l2_dev,
						  i2c_adap, &sdinfo->board_info,
						  NULL);
			if (vpfe_dev->sd[k]) {
				v4l2_info(&vpfe_dev->v4l2_dev,
						"v4l2 sub device %s registered\n",
						sdinfo->module_name);

				vpfe_dev->sd[k]->grp_id = sdinfo->grp_id;
				k++;

				sdinfo->registered = 1;
			}
		} else {
			v4l2_info(&vpfe_dev->v4l2_dev,
				  "v4l2 sub device %s is not registered\n",
				  sdinfo->module_name);
		}
	}
	vpfe_dev->num_ext_subdevs = k;

	return 0;

probe_sd_out:
	kzfree(vpfe_dev->sd);

	return ret;
}