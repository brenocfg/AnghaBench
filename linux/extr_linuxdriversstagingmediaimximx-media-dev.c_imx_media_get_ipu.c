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
struct v4l2_subdev {int name; TYPE_1__* dev; } ;
struct ipu_soc {int dummy; } ;
struct imx_media_dev {struct ipu_soc** ipu; int /*<<< orphan*/  v4l2_dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;

/* Variables and functions */
 int ENODEV ; 
 struct ipu_soc* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int ipu_get_num (struct ipu_soc*) ; 
 int /*<<< orphan*/  v4l2_err (int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static int imx_media_get_ipu(struct imx_media_dev *imxmd,
			     struct v4l2_subdev *csi_sd)
{
	struct ipu_soc *ipu;
	int ipu_id;

	ipu = dev_get_drvdata(csi_sd->dev->parent);
	if (!ipu) {
		v4l2_err(&imxmd->v4l2_dev,
			 "CSI %s has no parent IPU!\n", csi_sd->name);
		return -ENODEV;
	}

	ipu_id = ipu_get_num(ipu);
	if (ipu_id > 1) {
		v4l2_err(&imxmd->v4l2_dev, "invalid IPU id %d!\n", ipu_id);
		return -ENODEV;
	}

	if (!imxmd->ipu[ipu_id])
		imxmd->ipu[ipu_id] = ipu;

	return 0;
}