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
struct device {int dummy; } ;

/* Variables and functions */
#define  WM8988_3D 161 
#define  WM8988_ADCDAC 160 
#define  WM8988_ADCIN 159 
#define  WM8988_ADCTL1 158 
#define  WM8988_ADCTL2 157 
#define  WM8988_ADCTL3 156 
#define  WM8988_ALC1 155 
#define  WM8988_ALC2 154 
#define  WM8988_ALC3 153 
#define  WM8988_BASS 152 
#define  WM8988_IFACE 151 
#define  WM8988_LADC 150 
#define  WM8988_LADCIN 149 
#define  WM8988_LDAC 148 
#define  WM8988_LINVOL 147 
#define  WM8988_LOUT1V 146 
#define  WM8988_LOUT2V 145 
#define  WM8988_LOUTM1 144 
#define  WM8988_LOUTM2 143 
#define  WM8988_LPPB 142 
#define  WM8988_NGATE 141 
#define  WM8988_PWR1 140 
#define  WM8988_PWR2 139 
#define  WM8988_RADC 138 
#define  WM8988_RADCIN 137 
#define  WM8988_RDAC 136 
#define  WM8988_RESET 135 
#define  WM8988_RINVOL 134 
#define  WM8988_ROUT1V 133 
#define  WM8988_ROUT2V 132 
#define  WM8988_ROUTM1 131 
#define  WM8988_ROUTM2 130 
#define  WM8988_SRATE 129 
#define  WM8988_TREBLE 128 

__attribute__((used)) static bool wm8988_writeable(struct device *dev, unsigned int reg)
{
	switch (reg) {
	case WM8988_LINVOL:
	case WM8988_RINVOL:
	case WM8988_LOUT1V:
	case WM8988_ROUT1V:
	case WM8988_ADCDAC:
	case WM8988_IFACE:
	case WM8988_SRATE:
	case WM8988_LDAC:
	case WM8988_RDAC:
	case WM8988_BASS:
	case WM8988_TREBLE:
	case WM8988_RESET:
	case WM8988_3D:
	case WM8988_ALC1:
	case WM8988_ALC2:
	case WM8988_ALC3:
	case WM8988_NGATE:
	case WM8988_LADC:
	case WM8988_RADC:
	case WM8988_ADCTL1:
	case WM8988_ADCTL2:
	case WM8988_PWR1:
	case WM8988_PWR2:
	case WM8988_ADCTL3:
	case WM8988_ADCIN:
	case WM8988_LADCIN:
	case WM8988_RADCIN:
	case WM8988_LOUTM1:
	case WM8988_LOUTM2:
	case WM8988_ROUTM1:
	case WM8988_ROUTM2:
	case WM8988_LOUT2V:
	case WM8988_ROUT2V:
	case WM8988_LPPB:
		return true;
	default:
		return false;
	}
}