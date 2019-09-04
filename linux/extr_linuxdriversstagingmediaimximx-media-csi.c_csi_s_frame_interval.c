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
struct v4l2_fract {int dummy; } ;
struct v4l2_subdev_frame_interval {int pad; struct v4l2_fract interval; } ;
struct v4l2_subdev {int dummy; } ;
struct csi_priv {int /*<<< orphan*/  lock; struct v4l2_fract* frame_interval; int /*<<< orphan*/ * skip; } ;

/* Variables and functions */
#define  CSI_SINK_PAD 130 
#define  CSI_SRC_PAD_DIRECT 129 
#define  CSI_SRC_PAD_IDMAC 128 
 int EINVAL ; 
 int /*<<< orphan*/ * csi_find_best_skip (struct v4l2_fract*,struct v4l2_fract*) ; 
 int /*<<< orphan*/ * csi_skip ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct csi_priv* v4l2_get_subdevdata (struct v4l2_subdev*) ; 

__attribute__((used)) static int csi_s_frame_interval(struct v4l2_subdev *sd,
				struct v4l2_subdev_frame_interval *fi)
{
	struct csi_priv *priv = v4l2_get_subdevdata(sd);
	struct v4l2_fract *input_fi;
	int ret = 0;

	mutex_lock(&priv->lock);

	input_fi = &priv->frame_interval[CSI_SINK_PAD];

	switch (fi->pad) {
	case CSI_SINK_PAD:
		/* No limits on input frame interval */
		/* Reset output intervals and frame skipping ratio to 1:1 */
		priv->frame_interval[CSI_SRC_PAD_IDMAC] = fi->interval;
		priv->frame_interval[CSI_SRC_PAD_DIRECT] = fi->interval;
		priv->skip = &csi_skip[0];
		break;
	case CSI_SRC_PAD_IDMAC:
		/*
		 * frame interval at IDMAC output pad depends on input
		 * interval, modified by frame skipping.
		 */
		priv->skip = csi_find_best_skip(input_fi, &fi->interval);
		break;
	case CSI_SRC_PAD_DIRECT:
		/*
		 * frame interval at DIRECT output pad is same as input
		 * interval.
		 */
		fi->interval = *input_fi;
		break;
	default:
		ret = -EINVAL;
		goto out;
	}

	priv->frame_interval[fi->pad] = fi->interval;
out:
	mutex_unlock(&priv->lock);
	return ret;
}