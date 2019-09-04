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
struct vdic_priv {scalar_t__ motion; int /*<<< orphan*/  lock; int /*<<< orphan*/  sd; scalar_t__ csi_direct; } ;
struct v4l2_subdev_format {int dummy; } ;
struct v4l2_subdev {int dummy; } ;
struct media_link {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ HIGH_MOTION ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_err (int /*<<< orphan*/ *,char*) ; 
 struct vdic_priv* v4l2_get_subdevdata (struct v4l2_subdev*) ; 
 int v4l2_subdev_link_validate_default (struct v4l2_subdev*,struct media_link*,struct v4l2_subdev_format*,struct v4l2_subdev_format*) ; 

__attribute__((used)) static int vdic_link_validate(struct v4l2_subdev *sd,
			      struct media_link *link,
			      struct v4l2_subdev_format *source_fmt,
			      struct v4l2_subdev_format *sink_fmt)
{
	struct vdic_priv *priv = v4l2_get_subdevdata(sd);
	int ret;

	ret = v4l2_subdev_link_validate_default(sd, link,
						source_fmt, sink_fmt);
	if (ret)
		return ret;

	mutex_lock(&priv->lock);

	if (priv->csi_direct && priv->motion != HIGH_MOTION) {
		v4l2_err(&priv->sd,
			 "direct CSI pipeline requires high motion\n");
		ret = -EINVAL;
	}

	mutex_unlock(&priv->lock);
	return ret;
}