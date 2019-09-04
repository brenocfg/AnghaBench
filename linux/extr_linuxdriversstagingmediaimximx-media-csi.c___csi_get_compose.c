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
struct v4l2_subdev_pad_config {int dummy; } ;
struct v4l2_rect {int dummy; } ;
struct csi_priv {struct v4l2_rect compose; int /*<<< orphan*/  sd; } ;
typedef  enum v4l2_subdev_format_whence { ____Placeholder_v4l2_subdev_format_whence } v4l2_subdev_format_whence ;

/* Variables and functions */
 int /*<<< orphan*/  CSI_SINK_PAD ; 
 int V4L2_SUBDEV_FORMAT_TRY ; 
 struct v4l2_rect* v4l2_subdev_get_try_compose (int /*<<< orphan*/ *,struct v4l2_subdev_pad_config*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct v4l2_rect *
__csi_get_compose(struct csi_priv *priv, struct v4l2_subdev_pad_config *cfg,
		  enum v4l2_subdev_format_whence which)
{
	if (which == V4L2_SUBDEV_FORMAT_TRY)
		return v4l2_subdev_get_try_compose(&priv->sd, cfg,
						   CSI_SINK_PAD);
	else
		return &priv->compose;
}