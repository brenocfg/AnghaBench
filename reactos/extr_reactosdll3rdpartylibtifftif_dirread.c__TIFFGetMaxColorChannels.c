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
typedef  int uint16 ;

/* Variables and functions */
#define  PHOTOMETRIC_CFA 140 
#define  PHOTOMETRIC_CIELAB 139 
#define  PHOTOMETRIC_ICCLAB 138 
#define  PHOTOMETRIC_ITULAB 137 
#define  PHOTOMETRIC_LOGL 136 
#define  PHOTOMETRIC_LOGLUV 135 
#define  PHOTOMETRIC_MASK 134 
#define  PHOTOMETRIC_MINISBLACK 133 
#define  PHOTOMETRIC_MINISWHITE 132 
#define  PHOTOMETRIC_PALETTE 131 
#define  PHOTOMETRIC_RGB 130 
#define  PHOTOMETRIC_SEPARATED 129 
#define  PHOTOMETRIC_YCBCR 128 

__attribute__((used)) static int _TIFFGetMaxColorChannels( uint16 photometric )
{
    switch (photometric) {
	case PHOTOMETRIC_PALETTE:
	case PHOTOMETRIC_MINISWHITE:
	case PHOTOMETRIC_MINISBLACK:
            return 1;
	case PHOTOMETRIC_YCBCR:
	case PHOTOMETRIC_RGB:
	case PHOTOMETRIC_CIELAB:
	case PHOTOMETRIC_LOGLUV:
	case PHOTOMETRIC_ITULAB:
	case PHOTOMETRIC_ICCLAB:
            return 3;
	case PHOTOMETRIC_SEPARATED:
	case PHOTOMETRIC_MASK:
            return 4;
	case PHOTOMETRIC_LOGL:
	case PHOTOMETRIC_CFA:
	default:
            return 0;
    }
}