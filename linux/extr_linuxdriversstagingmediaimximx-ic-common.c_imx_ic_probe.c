#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_7__ ;
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {struct imx_media_internal_sd_platformdata* platform_data; } ;
struct platform_device {TYPE_7__ dev; } ;
struct imx_media_internal_sd_platformdata {int grp_id; int /*<<< orphan*/  sd_name; int /*<<< orphan*/  ipu_id; } ;
struct TYPE_8__ {int /*<<< orphan*/  function; int /*<<< orphan*/  ops; } ;
struct TYPE_9__ {int flags; int grp_id; int /*<<< orphan*/  name; int /*<<< orphan*/  owner; TYPE_7__* dev; TYPE_1__ entity; int /*<<< orphan*/  internal_ops; } ;
struct imx_ic_priv {size_t task_id; TYPE_2__ sd; int /*<<< orphan*/  ipu_id; TYPE_7__* dev; } ;
struct TYPE_10__ {int (* init ) (struct imx_ic_priv*) ;int /*<<< orphan*/  (* remove ) (struct imx_ic_priv*) ;int /*<<< orphan*/  entity_ops; int /*<<< orphan*/  internal_ops; int /*<<< orphan*/  subdev_ops; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 size_t IC_TASK_ENCODER ; 
 size_t IC_TASK_PRP ; 
 size_t IC_TASK_VIEWFINDER ; 
#define  IMX_MEDIA_GRP_ID_IC_PRP 130 
#define  IMX_MEDIA_GRP_ID_IC_PRPENC 129 
#define  IMX_MEDIA_GRP_ID_IC_PRPVF 128 
 int /*<<< orphan*/  MEDIA_ENT_F_PROC_VIDEO_SCALER ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int V4L2_SUBDEV_FL_HAS_DEVNODE ; 
 int V4L2_SUBDEV_FL_HAS_EVENTS ; 
 struct imx_ic_priv* devm_kzalloc (TYPE_7__*,int,int /*<<< orphan*/ ) ; 
 TYPE_6__** ic_ops ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,TYPE_2__*) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int stub1 (struct imx_ic_priv*) ; 
 int /*<<< orphan*/  stub2 (struct imx_ic_priv*) ; 
 int v4l2_async_register_subdev (TYPE_2__*) ; 
 int /*<<< orphan*/  v4l2_set_subdevdata (TYPE_2__*,struct imx_ic_priv*) ; 
 int /*<<< orphan*/  v4l2_subdev_init (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int imx_ic_probe(struct platform_device *pdev)
{
	struct imx_media_internal_sd_platformdata *pdata;
	struct imx_ic_priv *priv;
	int ret;

	priv = devm_kzalloc(&pdev->dev, sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	platform_set_drvdata(pdev, &priv->sd);
	priv->dev = &pdev->dev;

	/* get our ipu_id, grp_id and IC task id */
	pdata = priv->dev->platform_data;
	priv->ipu_id = pdata->ipu_id;
	switch (pdata->grp_id) {
	case IMX_MEDIA_GRP_ID_IC_PRP:
		priv->task_id = IC_TASK_PRP;
		break;
	case IMX_MEDIA_GRP_ID_IC_PRPENC:
		priv->task_id = IC_TASK_ENCODER;
		break;
	case IMX_MEDIA_GRP_ID_IC_PRPVF:
		priv->task_id = IC_TASK_VIEWFINDER;
		break;
	default:
		return -EINVAL;
	}

	v4l2_subdev_init(&priv->sd, ic_ops[priv->task_id]->subdev_ops);
	v4l2_set_subdevdata(&priv->sd, priv);
	priv->sd.internal_ops = ic_ops[priv->task_id]->internal_ops;
	priv->sd.entity.ops = ic_ops[priv->task_id]->entity_ops;
	priv->sd.entity.function = MEDIA_ENT_F_PROC_VIDEO_SCALER;
	priv->sd.dev = &pdev->dev;
	priv->sd.owner = THIS_MODULE;
	priv->sd.flags = V4L2_SUBDEV_FL_HAS_DEVNODE | V4L2_SUBDEV_FL_HAS_EVENTS;
	priv->sd.grp_id = pdata->grp_id;
	strncpy(priv->sd.name, pdata->sd_name, sizeof(priv->sd.name));

	ret = ic_ops[priv->task_id]->init(priv);
	if (ret)
		return ret;

	ret = v4l2_async_register_subdev(&priv->sd);
	if (ret)
		ic_ops[priv->task_id]->remove(priv);

	return ret;
}