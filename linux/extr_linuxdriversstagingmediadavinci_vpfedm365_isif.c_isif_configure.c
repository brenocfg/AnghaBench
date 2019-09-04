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
struct vpfe_isif_device {struct v4l2_mbus_framefmt* formats; } ;
struct v4l2_subdev {int dummy; } ;
struct v4l2_mbus_framefmt {int code; } ;

/* Variables and functions */
 int EINVAL ; 
 size_t ISIF_PAD_SINK ; 
#define  MEDIA_BUS_FMT_SGRBG10_ALAW8_1X8 136 
#define  MEDIA_BUS_FMT_SGRBG10_DPCM8_1X8 135 
#define  MEDIA_BUS_FMT_SGRBG12_1X12 134 
#define  MEDIA_BUS_FMT_UYVY8_2X8 133 
#define  MEDIA_BUS_FMT_Y8_1X8 132 
#define  MEDIA_BUS_FMT_YUYV10_1X20 131 
#define  MEDIA_BUS_FMT_YUYV10_2X10 130 
#define  MEDIA_BUS_FMT_YUYV8_1X16 129 
#define  MEDIA_BUS_FMT_YUYV8_2X8 128 
 int isif_config_raw (struct v4l2_subdev*,int) ; 
 int isif_config_ycbcr (struct v4l2_subdev*,int) ; 
 struct vpfe_isif_device* v4l2_get_subdevdata (struct v4l2_subdev*) ; 

__attribute__((used)) static int isif_configure(struct v4l2_subdev *sd, int mode)
{
	struct vpfe_isif_device *isif = v4l2_get_subdevdata(sd);
	struct v4l2_mbus_framefmt *format;

	format = &isif->formats[ISIF_PAD_SINK];

	switch (format->code) {
	case MEDIA_BUS_FMT_SGRBG10_ALAW8_1X8:
	case MEDIA_BUS_FMT_SGRBG10_DPCM8_1X8:
	case MEDIA_BUS_FMT_SGRBG12_1X12:
		return isif_config_raw(sd, mode);

	case MEDIA_BUS_FMT_YUYV8_2X8:
	case MEDIA_BUS_FMT_UYVY8_2X8:
	case MEDIA_BUS_FMT_YUYV10_2X10:
	case MEDIA_BUS_FMT_Y8_1X8:
	case MEDIA_BUS_FMT_YUYV8_1X16:
	case MEDIA_BUS_FMT_YUYV10_1X20:
		return isif_config_ycbcr(sd, mode);

	default:
		break;
	}
	return -EINVAL;
}