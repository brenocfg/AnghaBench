#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct v4l2_subdev {TYPE_1__* v4l2_dev; int /*<<< orphan*/  dev; } ;
struct imx_media_fim {int /*<<< orphan*/  lock; struct v4l2_subdev* sd; int /*<<< orphan*/  md; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct imx_media_fim* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_get_drvdata (int /*<<< orphan*/ ) ; 
 struct imx_media_fim* devm_kzalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int init_fim_controls (struct imx_media_fim*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

struct imx_media_fim *imx_media_fim_init(struct v4l2_subdev *sd)
{
	struct imx_media_fim *fim;
	int ret;

	fim = devm_kzalloc(sd->dev, sizeof(*fim), GFP_KERNEL);
	if (!fim)
		return ERR_PTR(-ENOMEM);

	/* get media device */
	fim->md = dev_get_drvdata(sd->v4l2_dev->dev);
	fim->sd = sd;

	spin_lock_init(&fim->lock);

	ret = init_fim_controls(fim);
	if (ret)
		return ERR_PTR(ret);

	return fim;
}