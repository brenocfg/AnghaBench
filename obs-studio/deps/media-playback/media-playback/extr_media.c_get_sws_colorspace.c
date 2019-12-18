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
typedef  enum AVColorSpace { ____Placeholder_AVColorSpace } AVColorSpace ;

/* Variables and functions */
#define  AVCOL_SPC_BT709 131 
#define  AVCOL_SPC_FCC 130 
#define  AVCOL_SPC_SMPTE170M 129 
#define  AVCOL_SPC_SMPTE240M 128 
 int SWS_CS_FCC ; 
 int SWS_CS_ITU601 ; 
 int SWS_CS_ITU709 ; 
 int SWS_CS_SMPTE170M ; 
 int SWS_CS_SMPTE240M ; 

__attribute__((used)) static inline int get_sws_colorspace(enum AVColorSpace cs)
{
	switch (cs) {
	case AVCOL_SPC_BT709:
		return SWS_CS_ITU709;
	case AVCOL_SPC_FCC:
		return SWS_CS_FCC;
	case AVCOL_SPC_SMPTE170M:
		return SWS_CS_SMPTE170M;
	case AVCOL_SPC_SMPTE240M:
		return SWS_CS_SMPTE240M;
	default:
		break;
	}

	return SWS_CS_ITU601;
}