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
typedef  int u16 ;
struct video_device {int dummy; } ;
struct v4l2_subdev {int dummy; } ;
struct mt9t031 {int xskip; int yskip; } ;
struct i2c_client {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MT9T031_COLUMN_ADDRESS_MODE ; 
 int /*<<< orphan*/  MT9T031_ROW_ADDRESS_MODE ; 
 int min (int,int) ; 
 int reg_write (struct i2c_client*,int /*<<< orphan*/ ,int) ; 
 struct v4l2_subdev* soc_camera_vdev_to_subdev (struct video_device*) ; 
 struct mt9t031* to_mt9t031 (struct i2c_client*) ; 
 struct video_device* to_video_device (struct device*) ; 
 struct i2c_client* v4l2_get_subdevdata (struct v4l2_subdev*) ; 

__attribute__((used)) static int mt9t031_runtime_resume(struct device *dev)
{
	struct video_device *vdev = to_video_device(dev);
	struct v4l2_subdev *sd = soc_camera_vdev_to_subdev(vdev);
	struct i2c_client *client = v4l2_get_subdevdata(sd);
	struct mt9t031 *mt9t031 = to_mt9t031(client);

	int ret;
	u16 xbin, ybin;

	xbin = min(mt9t031->xskip, (u16)3);
	ybin = min(mt9t031->yskip, (u16)3);

	ret = reg_write(client, MT9T031_COLUMN_ADDRESS_MODE,
		((xbin - 1) << 4) | (mt9t031->xskip - 1));
	if (ret < 0)
		return ret;

	ret = reg_write(client, MT9T031_ROW_ADDRESS_MODE,
		((ybin - 1) << 4) | (mt9t031->yskip - 1));
	if (ret < 0)
		return ret;

	return 0;
}