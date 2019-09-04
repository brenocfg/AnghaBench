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
 int IPIPEIF_5_1_PACK_12_BIT ; 
 int IPIPEIF_5_1_PACK_16_BIT ; 
 int IPIPEIF_5_1_PACK_8_BIT ; 
 int IPIPEIF_5_1_PACK_8_BIT_A_LAW ; 
#define  MEDIA_BUS_FMT_SBGGR12_1X12 134 
#define  MEDIA_BUS_FMT_SBGGR8_1X8 133 
#define  MEDIA_BUS_FMT_SGRBG10_ALAW8_1X8 132 
#define  MEDIA_BUS_FMT_SGRBG10_DPCM8_1X8 131 
#define  MEDIA_BUS_FMT_SGRBG12_1X12 130 
#define  MEDIA_BUS_FMT_UV8_1X8 129 
#define  MEDIA_BUS_FMT_Y8_1X8 128 

__attribute__((used)) static int
ipipeif_get_pack_mode(u32 in_pix_fmt)
{
	switch (in_pix_fmt) {
	case MEDIA_BUS_FMT_SBGGR8_1X8:
	case MEDIA_BUS_FMT_Y8_1X8:
	case MEDIA_BUS_FMT_SGRBG10_DPCM8_1X8:
	case MEDIA_BUS_FMT_UV8_1X8:
		return IPIPEIF_5_1_PACK_8_BIT;

	case MEDIA_BUS_FMT_SGRBG10_ALAW8_1X8:
		return IPIPEIF_5_1_PACK_8_BIT_A_LAW;

	case MEDIA_BUS_FMT_SGRBG12_1X12:
		return IPIPEIF_5_1_PACK_16_BIT;

	case MEDIA_BUS_FMT_SBGGR12_1X12:
		return IPIPEIF_5_1_PACK_12_BIT;

	default:
		return IPIPEIF_5_1_PACK_16_BIT;
	}
}