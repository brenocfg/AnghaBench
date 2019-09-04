#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {unsigned int v4l2_pix_fmt; int /*<<< orphan*/  pix_order; } ;
struct TYPE_6__ {unsigned int v4l2_pix_fmt; int /*<<< orphan*/  pix_fmt; } ;
struct TYPE_8__ {TYPE_3__ ycbcr; void* data_pack; TYPE_2__ bayer; } ;
struct vpfe_isif_device {TYPE_4__ isif_cfg; TYPE_1__* formats; } ;
struct TYPE_5__ {scalar_t__ code; } ;

/* Variables and functions */
 int EINVAL ; 
 void* ISIF_PACK_16BIT ; 
 void* ISIF_PACK_8BIT ; 
 size_t ISIF_PAD_SINK ; 
 int /*<<< orphan*/  ISIF_PIXFMT_RAW ; 
 int /*<<< orphan*/  ISIF_PIXORDER_CBYCRY ; 
 int /*<<< orphan*/  ISIF_PIXORDER_YCBYCR ; 
 scalar_t__ MEDIA_BUS_FMT_SGRBG12_1X12 ; 
 unsigned int V4L2_PIX_FMT_SBGGR16 ; 
 unsigned int V4L2_PIX_FMT_SGRBG10ALAW8 ; 
 unsigned int V4L2_PIX_FMT_SGRBG10DPCM8 ; 
 unsigned int V4L2_PIX_FMT_UYVY ; 
 unsigned int V4L2_PIX_FMT_YUYV ; 

__attribute__((used)) static int
isif_set_pixel_format(struct vpfe_isif_device *isif, unsigned int pixfmt)
{
	if (isif->formats[ISIF_PAD_SINK].code == MEDIA_BUS_FMT_SGRBG12_1X12) {
		if (pixfmt == V4L2_PIX_FMT_SBGGR16)
			isif->isif_cfg.data_pack = ISIF_PACK_16BIT;
		else if ((pixfmt == V4L2_PIX_FMT_SGRBG10DPCM8) ||
				(pixfmt == V4L2_PIX_FMT_SGRBG10ALAW8))
			isif->isif_cfg.data_pack = ISIF_PACK_8BIT;
		else
			return -EINVAL;

		isif->isif_cfg.bayer.pix_fmt = ISIF_PIXFMT_RAW;
		isif->isif_cfg.bayer.v4l2_pix_fmt = pixfmt;
	} else {
		if (pixfmt == V4L2_PIX_FMT_YUYV)
			isif->isif_cfg.ycbcr.pix_order = ISIF_PIXORDER_YCBYCR;
		else if (pixfmt == V4L2_PIX_FMT_UYVY)
			isif->isif_cfg.ycbcr.pix_order = ISIF_PIXORDER_CBYCRY;
		else
			return -EINVAL;

		isif->isif_cfg.data_pack = ISIF_PACK_8BIT;
		isif->isif_cfg.ycbcr.v4l2_pix_fmt = pixfmt;
	}

	return 0;
}