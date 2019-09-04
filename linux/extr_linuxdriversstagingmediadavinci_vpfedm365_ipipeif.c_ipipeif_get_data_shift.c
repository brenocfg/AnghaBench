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
struct vpfe_ipipeif_device {struct v4l2_mbus_framefmt* formats; } ;
struct v4l2_mbus_framefmt {int code; } ;

/* Variables and functions */
 int IPIPEIF_5_1_BITS11_0 ; 
 int IPIPEIF_5_1_BITS7_0 ; 
 size_t IPIPEIF_PAD_SINK ; 
#define  MEDIA_BUS_FMT_SGRBG12_1X12 130 
#define  MEDIA_BUS_FMT_UV8_1X8 129 
#define  MEDIA_BUS_FMT_Y8_1X8 128 

__attribute__((used)) static int
ipipeif_get_data_shift(struct vpfe_ipipeif_device *ipipeif)
{
	struct v4l2_mbus_framefmt *informat;

	informat = &ipipeif->formats[IPIPEIF_PAD_SINK];

	switch (informat->code) {
	case MEDIA_BUS_FMT_SGRBG12_1X12:
		return IPIPEIF_5_1_BITS11_0;

	case MEDIA_BUS_FMT_Y8_1X8:
	case MEDIA_BUS_FMT_UV8_1X8:
		return IPIPEIF_5_1_BITS11_0;

	default:
		return IPIPEIF_5_1_BITS7_0;
	}
}