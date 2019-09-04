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
typedef  int u32 ;

/* Variables and functions */
 int EINVAL ; 
 int ISIF_PIXFMT_RAW ; 
 int ISIF_PIXFMT_YCBCR_16BIT ; 
 int ISIF_PIXFMT_YCBCR_8BIT ; 
#define  MEDIA_BUS_FMT_SGRBG10_ALAW8_1X8 136 
#define  MEDIA_BUS_FMT_SGRBG10_DPCM8_1X8 135 
#define  MEDIA_BUS_FMT_SGRBG12_1X12 134 
#define  MEDIA_BUS_FMT_UYVY8_2X8 133 
#define  MEDIA_BUS_FMT_Y8_1X8 132 
#define  MEDIA_BUS_FMT_YUYV10_1X20 131 
#define  MEDIA_BUS_FMT_YUYV10_2X10 130 
#define  MEDIA_BUS_FMT_YUYV8_1X16 129 
#define  MEDIA_BUS_FMT_YUYV8_2X8 128 

__attribute__((used)) static int isif_get_pix_fmt(u32 mbus_code)
{
	switch (mbus_code) {
	case MEDIA_BUS_FMT_SGRBG10_ALAW8_1X8:
	case MEDIA_BUS_FMT_SGRBG10_DPCM8_1X8:
	case MEDIA_BUS_FMT_SGRBG12_1X12:
		return ISIF_PIXFMT_RAW;

	case MEDIA_BUS_FMT_YUYV8_2X8:
	case MEDIA_BUS_FMT_UYVY8_2X8:
	case MEDIA_BUS_FMT_YUYV10_2X10:
	case MEDIA_BUS_FMT_Y8_1X8:
		return ISIF_PIXFMT_YCBCR_8BIT;

	case MEDIA_BUS_FMT_YUYV8_1X16:
	case MEDIA_BUS_FMT_YUYV10_1X20:
		return ISIF_PIXFMT_YCBCR_16BIT;

	default:
		break;
	}
	return -EINVAL;
}