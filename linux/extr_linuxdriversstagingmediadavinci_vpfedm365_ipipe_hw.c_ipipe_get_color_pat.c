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
#define  MEDIA_BUS_FMT_SGRBG10_ALAW8_1X8 130 
#define  MEDIA_BUS_FMT_SGRBG10_DPCM8_1X8 129 
#define  MEDIA_BUS_FMT_SGRBG12_1X12 128 
 int ipipe_sgrbg_pattern ; 
 int ipipe_srggb_pattern ; 

__attribute__((used)) static u32 ipipe_get_color_pat(u32 pix)
{
	switch (pix) {
	case MEDIA_BUS_FMT_SGRBG10_ALAW8_1X8:
	case MEDIA_BUS_FMT_SGRBG10_DPCM8_1X8:
	case MEDIA_BUS_FMT_SGRBG12_1X12:
		return ipipe_sgrbg_pattern;

	default:
		return ipipe_srggb_pattern;
	}
}