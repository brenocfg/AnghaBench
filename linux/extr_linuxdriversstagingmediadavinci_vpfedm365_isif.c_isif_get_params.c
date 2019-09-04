#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  config_params; } ;
struct TYPE_6__ {TYPE_2__ bayer; } ;
struct vpfe_isif_device {TYPE_3__ isif_cfg; TYPE_1__* formats; } ;
struct v4l2_subdev {int dummy; } ;
struct TYPE_4__ {scalar_t__ code; } ;

/* Variables and functions */
 int EINVAL ; 
 size_t ISIF_PAD_SINK ; 
 scalar_t__ MEDIA_BUS_FMT_SGRBG12_1X12 ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ *,int) ; 
 struct vpfe_isif_device* v4l2_get_subdevdata (struct v4l2_subdev*) ; 

__attribute__((used)) static int isif_get_params(struct v4l2_subdev *sd, void *params)
{
	struct vpfe_isif_device *isif = v4l2_get_subdevdata(sd);

	/* only raw module parameters can be set through the IOCTL */
	if (isif->formats[ISIF_PAD_SINK].code != MEDIA_BUS_FMT_SGRBG12_1X12)
		return -EINVAL;
	memcpy(params, &isif->isif_cfg.bayer.config_params,
			sizeof(isif->isif_cfg.bayer.config_params));
	return 0;
}