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
struct v4l2_subdev {int grp_id; int /*<<< orphan*/  name; } ;
struct v4l2_async_subdev {int dummy; } ;
struct v4l2_async_notifier {int dummy; } ;
struct imx_media_dev {int /*<<< orphan*/  mutex; int /*<<< orphan*/  v4l2_dev; } ;

/* Variables and functions */
 int IMX_MEDIA_GRP_ID_CSI ; 
 int imx_media_get_ipu (struct imx_media_dev*,struct v4l2_subdev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct imx_media_dev* notifier2dev (struct v4l2_async_notifier*) ; 
 int /*<<< orphan*/  v4l2_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int imx_media_subdev_bound(struct v4l2_async_notifier *notifier,
				  struct v4l2_subdev *sd,
				  struct v4l2_async_subdev *asd)
{
	struct imx_media_dev *imxmd = notifier2dev(notifier);
	int ret = 0;

	mutex_lock(&imxmd->mutex);

	if (sd->grp_id & IMX_MEDIA_GRP_ID_CSI) {
		ret = imx_media_get_ipu(imxmd, sd);
		if (ret)
			goto out;
	}

	v4l2_info(&imxmd->v4l2_dev, "subdev %s bound\n", sd->name);
out:
	mutex_unlock(&imxmd->mutex);
	return ret;
}