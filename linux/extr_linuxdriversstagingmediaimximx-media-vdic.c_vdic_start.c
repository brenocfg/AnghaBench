#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct vdic_priv {size_t active_input_pad; TYPE_1__* ops; int /*<<< orphan*/  vdi; int /*<<< orphan*/  motion; scalar_t__ csi_direct; struct v4l2_mbus_framefmt* format_mbus; } ;
struct v4l2_mbus_framefmt {int /*<<< orphan*/  field; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct TYPE_3__ {int (* setup ) (struct vdic_priv*) ;int /*<<< orphan*/  (* start ) (struct vdic_priv*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  MEDIA_BUS_FMT_UYVY8_2X8 ; 
 int /*<<< orphan*/  V4L2_STD_UNKNOWN ; 
 TYPE_1__ direct_ops ; 
 TYPE_1__ indirect_ops ; 
 int /*<<< orphan*/  ipu_vdi_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipu_vdi_set_field_order (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipu_vdi_set_motion (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipu_vdi_setup (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub1 (struct vdic_priv*) ; 
 int /*<<< orphan*/  stub2 (struct vdic_priv*) ; 
 int vdic_get_ipu_resources (struct vdic_priv*) ; 
 int /*<<< orphan*/  vdic_put_ipu_resources (struct vdic_priv*) ; 

__attribute__((used)) static int vdic_start(struct vdic_priv *priv)
{
	struct v4l2_mbus_framefmt *infmt;
	int ret;

	infmt = &priv->format_mbus[priv->active_input_pad];

	priv->ops = priv->csi_direct ? &direct_ops : &indirect_ops;

	ret = vdic_get_ipu_resources(priv);
	if (ret)
		return ret;

	/*
	 * init the VDIC.
	 *
	 * note we don't give infmt->code to ipu_vdi_setup(). The VDIC
	 * only supports 4:2:2 or 4:2:0, and this subdev will only
	 * negotiate 4:2:2 at its sink pads.
	 */
	ipu_vdi_setup(priv->vdi, MEDIA_BUS_FMT_UYVY8_2X8,
		      infmt->width, infmt->height);
	ipu_vdi_set_field_order(priv->vdi, V4L2_STD_UNKNOWN, infmt->field);
	ipu_vdi_set_motion(priv->vdi, priv->motion);

	ret = priv->ops->setup(priv);
	if (ret)
		goto out_put_ipu;

	ipu_vdi_enable(priv->vdi);

	priv->ops->start(priv);

	return 0;

out_put_ipu:
	vdic_put_ipu_resources(priv);
	return ret;
}