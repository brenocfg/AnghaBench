#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct platform_device_info {int size_data; int /*<<< orphan*/  dma_mask; struct imx_media_internal_sd_platformdata* data; int /*<<< orphan*/  parent; scalar_t__ id; int /*<<< orphan*/  name; } ;
struct platform_device {int dummy; } ;
struct internal_subdev {TYPE_1__* id; } ;
struct imx_media_internal_sd_platformdata {int ipu_id; int /*<<< orphan*/  grp_id; int /*<<< orphan*/  sd_name; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct imx_media_dev {TYPE_2__ md; } ;
typedef  int /*<<< orphan*/  pdata ;
struct TYPE_3__ {scalar_t__ index; int /*<<< orphan*/  name; int /*<<< orphan*/  grp_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIT_MASK (int) ; 
 scalar_t__ IS_ERR (struct platform_device*) ; 
 int PTR_ERR (struct platform_device*) ; 
 int imx_media_add_async_subdev (struct imx_media_dev*,int /*<<< orphan*/ *,struct platform_device*) ; 
 int /*<<< orphan*/  imx_media_grp_id_to_sd_name (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int num_isd ; 
 struct platform_device* platform_device_register_full (struct platform_device_info*) ; 

__attribute__((used)) static int add_internal_subdev(struct imx_media_dev *imxmd,
			       const struct internal_subdev *isd,
			       int ipu_id)
{
	struct imx_media_internal_sd_platformdata pdata;
	struct platform_device_info pdevinfo = {};
	struct platform_device *pdev;

	pdata.grp_id = isd->id->grp_id;

	/* the id of IPU this subdev will control */
	pdata.ipu_id = ipu_id;

	/* create subdev name */
	imx_media_grp_id_to_sd_name(pdata.sd_name, sizeof(pdata.sd_name),
				    pdata.grp_id, ipu_id);

	pdevinfo.name = isd->id->name;
	pdevinfo.id = ipu_id * num_isd + isd->id->index;
	pdevinfo.parent = imxmd->md.dev;
	pdevinfo.data = &pdata;
	pdevinfo.size_data = sizeof(pdata);
	pdevinfo.dma_mask = DMA_BIT_MASK(32);

	pdev = platform_device_register_full(&pdevinfo);
	if (IS_ERR(pdev))
		return PTR_ERR(pdev);

	return imx_media_add_async_subdev(imxmd, NULL, pdev);
}