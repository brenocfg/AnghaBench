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
struct v4l2_pix_format {int /*<<< orphan*/  pixelformat; } ;
struct imx_media_video_dev {int dummy; } ;
struct TYPE_4__ {struct v4l2_pix_format pix; } ;
struct TYPE_5__ {TYPE_1__ fmt; } ;
struct TYPE_6__ {int /*<<< orphan*/  cc; TYPE_2__ fmt; } ;
struct capture_priv {int /*<<< orphan*/  mutex; TYPE_3__ vdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CS_SEL_ANY ; 
 int /*<<< orphan*/  imx_media_find_format (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct capture_priv* to_capture_priv (struct imx_media_video_dev*) ; 

void imx_media_capture_device_set_format(struct imx_media_video_dev *vdev,
					 struct v4l2_pix_format *pix)
{
	struct capture_priv *priv = to_capture_priv(vdev);

	mutex_lock(&priv->mutex);
	priv->vdev.fmt.fmt.pix = *pix;
	priv->vdev.cc = imx_media_find_format(pix->pixelformat, CS_SEL_ANY,
					      true);
	mutex_unlock(&priv->mutex);
}