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
struct v4l2_subdev_mbus_code_enum {int pad; int /*<<< orphan*/  code; int /*<<< orphan*/  which; int /*<<< orphan*/  index; } ;
struct v4l2_subdev {int dummy; } ;
struct v4l2_mbus_framefmt {int /*<<< orphan*/  code; } ;
struct prp_priv {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  CS_SEL_ANY ; 
 int EINVAL ; 
#define  PRP_SINK_PAD 130 
#define  PRP_SRC_PAD_PRPENC 129 
#define  PRP_SRC_PAD_PRPVF 128 
 struct v4l2_mbus_framefmt* __prp_get_fmt (struct prp_priv*,struct v4l2_subdev_pad_config*,int const,int /*<<< orphan*/ ) ; 
 int imx_media_enum_ipu_format (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct prp_priv* sd_to_priv (struct v4l2_subdev*) ; 

__attribute__((used)) static int prp_enum_mbus_code(struct v4l2_subdev *sd,
			      struct v4l2_subdev_pad_config *cfg,
			      struct v4l2_subdev_mbus_code_enum *code)
{
	struct prp_priv *priv = sd_to_priv(sd);
	struct v4l2_mbus_framefmt *infmt;
	int ret = 0;

	mutex_lock(&priv->lock);

	switch (code->pad) {
	case PRP_SINK_PAD:
		ret = imx_media_enum_ipu_format(&code->code, code->index,
						CS_SEL_ANY);
		break;
	case PRP_SRC_PAD_PRPENC:
	case PRP_SRC_PAD_PRPVF:
		if (code->index != 0) {
			ret = -EINVAL;
			goto out;
		}
		infmt = __prp_get_fmt(priv, cfg, PRP_SINK_PAD, code->which);
		code->code = infmt->code;
		break;
	default:
		ret = -EINVAL;
	}
out:
	mutex_unlock(&priv->lock);
	return ret;
}