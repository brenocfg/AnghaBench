#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_6__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  function; int /*<<< orphan*/ * ops; } ;
struct TYPE_8__ {int /*<<< orphan*/  name; int /*<<< orphan*/  grp_id; int /*<<< orphan*/  flags; int /*<<< orphan*/  owner; TYPE_6__* dev; TYPE_1__ entity; int /*<<< orphan*/ * internal_ops; } ;
struct vdic_priv {int /*<<< orphan*/  lock; TYPE_2__ sd; int /*<<< orphan*/  ipu_id; TYPE_6__* dev; } ;
struct TYPE_9__ {struct imx_media_internal_sd_platformdata* platform_data; } ;
struct platform_device {TYPE_6__ dev; } ;
struct imx_media_internal_sd_platformdata {int /*<<< orphan*/  sd_name; int /*<<< orphan*/  grp_id; int /*<<< orphan*/  ipu_id; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MEDIA_ENT_F_PROC_VIDEO_PIXEL_FORMATTER ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  V4L2_SUBDEV_FL_HAS_DEVNODE ; 
 struct vdic_priv* devm_kzalloc (TYPE_6__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,TYPE_2__*) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int v4l2_async_register_subdev (TYPE_2__*) ; 
 int /*<<< orphan*/  v4l2_set_subdevdata (TYPE_2__*,struct vdic_priv*) ; 
 int /*<<< orphan*/  v4l2_subdev_init (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vdic_entity_ops ; 
 int /*<<< orphan*/  vdic_internal_ops ; 
 int /*<<< orphan*/  vdic_subdev_ops ; 

__attribute__((used)) static int imx_vdic_probe(struct platform_device *pdev)
{
	struct imx_media_internal_sd_platformdata *pdata;
	struct vdic_priv *priv;
	int ret;

	priv = devm_kzalloc(&pdev->dev, sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	platform_set_drvdata(pdev, &priv->sd);
	priv->dev = &pdev->dev;

	pdata = priv->dev->platform_data;
	priv->ipu_id = pdata->ipu_id;

	v4l2_subdev_init(&priv->sd, &vdic_subdev_ops);
	v4l2_set_subdevdata(&priv->sd, priv);
	priv->sd.internal_ops = &vdic_internal_ops;
	priv->sd.entity.ops = &vdic_entity_ops;
	priv->sd.entity.function = MEDIA_ENT_F_PROC_VIDEO_PIXEL_FORMATTER;
	priv->sd.dev = &pdev->dev;
	priv->sd.owner = THIS_MODULE;
	priv->sd.flags = V4L2_SUBDEV_FL_HAS_DEVNODE;
	/* get our group id */
	priv->sd.grp_id = pdata->grp_id;
	strncpy(priv->sd.name, pdata->sd_name, sizeof(priv->sd.name));

	mutex_init(&priv->lock);

	ret = v4l2_async_register_subdev(&priv->sd);
	if (ret)
		goto free;

	return 0;
free:
	mutex_destroy(&priv->lock);
	return ret;
}