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

/* Variables and functions */
 unsigned int CRT1_LCDA ; 
 unsigned int CRT2_LCD ; 
 unsigned short* ModeIndex_1024x576 ; 
 unsigned short* ModeIndex_1024x600 ; 
 unsigned short* ModeIndex_1024x768 ; 
 unsigned short* ModeIndex_1152x768 ; 
 unsigned short* ModeIndex_1152x864 ; 
 unsigned short* ModeIndex_1280x1024 ; 
 unsigned short* ModeIndex_1280x720 ; 
 unsigned short* ModeIndex_1280x800 ; 
 unsigned short* ModeIndex_1280x854 ; 
 unsigned short* ModeIndex_1280x960 ; 
 unsigned short* ModeIndex_1360x768 ; 
 unsigned short* ModeIndex_1400x1050 ; 
 unsigned short* ModeIndex_1600x1200 ; 
 unsigned short* ModeIndex_1680x1050 ; 
 unsigned short* ModeIndex_1920x1080 ; 
 unsigned short* ModeIndex_1920x1440 ; 
 unsigned short* ModeIndex_300_1280x768 ; 
 unsigned short* ModeIndex_300_1360x1024 ; 
 unsigned short* ModeIndex_300_2048x1536 ; 
 unsigned short* ModeIndex_310_1280x768 ; 
 unsigned short* ModeIndex_310_2048x1536 ; 
 unsigned short* ModeIndex_320x200 ; 
 unsigned short* ModeIndex_320x240 ; 
 unsigned short* ModeIndex_320x240_FSTN ; 
 unsigned short* ModeIndex_400x300 ; 
 unsigned short* ModeIndex_512x384 ; 
 unsigned short* ModeIndex_640x400 ; 
 unsigned short* ModeIndex_640x480 ; 
 unsigned short* ModeIndex_720x480 ; 
 unsigned short* ModeIndex_720x576 ; 
 unsigned short* ModeIndex_768x576 ; 
 unsigned short* ModeIndex_800x480 ; 
 unsigned short* ModeIndex_800x600 ; 
 unsigned short* ModeIndex_848x480 ; 
 unsigned short* ModeIndex_856x480 ; 
 unsigned short* ModeIndex_960x540 ; 
 unsigned short* ModeIndex_960x600 ; 
 int SIS_300_VGA ; 
 int SIS_315_VGA ; 

__attribute__((used)) static
unsigned short
SiS_GetModeID(int VGAEngine, unsigned int VBFlags, int HDisplay, int VDisplay,
		int Depth, bool FSTN, int LCDwidth, int LCDheight)
{
   unsigned short ModeIndex = 0;

   switch(HDisplay)
   {
	case 320:
		if(VDisplay == 200) ModeIndex = ModeIndex_320x200[Depth];
		else if(VDisplay == 240) {
			if((VBFlags & CRT2_LCD) && (FSTN))
				ModeIndex = ModeIndex_320x240_FSTN[Depth];
			else
				ModeIndex = ModeIndex_320x240[Depth];
		}
		break;
	case 400:
		if((!(VBFlags & CRT1_LCDA)) || ((LCDwidth >= 800) && (LCDwidth >= 600))) {
			if(VDisplay == 300) ModeIndex = ModeIndex_400x300[Depth];
		}
		break;
	case 512:
		if((!(VBFlags & CRT1_LCDA)) || ((LCDwidth >= 1024) && (LCDwidth >= 768))) {
			if(VDisplay == 384) ModeIndex = ModeIndex_512x384[Depth];
		}
		break;
	case 640:
		if(VDisplay == 480)      ModeIndex = ModeIndex_640x480[Depth];
		else if(VDisplay == 400) ModeIndex = ModeIndex_640x400[Depth];
		break;
	case 720:
		if(VDisplay == 480)      ModeIndex = ModeIndex_720x480[Depth];
		else if(VDisplay == 576) ModeIndex = ModeIndex_720x576[Depth];
		break;
	case 768:
		if(VDisplay == 576) ModeIndex = ModeIndex_768x576[Depth];
		break;
	case 800:
		if(VDisplay == 600)      ModeIndex = ModeIndex_800x600[Depth];
		else if(VDisplay == 480) ModeIndex = ModeIndex_800x480[Depth];
		break;
	case 848:
		if(VDisplay == 480) ModeIndex = ModeIndex_848x480[Depth];
		break;
	case 856:
		if(VDisplay == 480) ModeIndex = ModeIndex_856x480[Depth];
		break;
	case 960:
		if(VGAEngine == SIS_315_VGA) {
			if(VDisplay == 540)      ModeIndex = ModeIndex_960x540[Depth];
			else if(VDisplay == 600) ModeIndex = ModeIndex_960x600[Depth];
		}
		break;
	case 1024:
		if(VDisplay == 576)      ModeIndex = ModeIndex_1024x576[Depth];
		else if(VDisplay == 768) ModeIndex = ModeIndex_1024x768[Depth];
		else if(VGAEngine == SIS_300_VGA) {
			if(VDisplay == 600) ModeIndex = ModeIndex_1024x600[Depth];
		}
		break;
	case 1152:
		if(VDisplay == 864) ModeIndex = ModeIndex_1152x864[Depth];
		if(VGAEngine == SIS_300_VGA) {
			if(VDisplay == 768) ModeIndex = ModeIndex_1152x768[Depth];
		}
		break;
	case 1280:
		switch(VDisplay) {
			case 720:
				ModeIndex = ModeIndex_1280x720[Depth];
				break;
			case 768:
				if(VGAEngine == SIS_300_VGA) {
					ModeIndex = ModeIndex_300_1280x768[Depth];
				} else {
					ModeIndex = ModeIndex_310_1280x768[Depth];
				}
				break;
			case 800:
				if(VGAEngine == SIS_315_VGA) {
					ModeIndex = ModeIndex_1280x800[Depth];
				}
				break;
			case 854:
				if(VGAEngine == SIS_315_VGA) {
					ModeIndex = ModeIndex_1280x854[Depth];
				}
				break;
			case 960:
				ModeIndex = ModeIndex_1280x960[Depth];
				break;
			case 1024:
				ModeIndex = ModeIndex_1280x1024[Depth];
				break;
		}
		break;
	case 1360:
		if(VDisplay == 768) ModeIndex = ModeIndex_1360x768[Depth];
		if(VGAEngine == SIS_300_VGA) {
			if(VDisplay == 1024) ModeIndex = ModeIndex_300_1360x1024[Depth];
		}
		break;
	case 1400:
		if(VGAEngine == SIS_315_VGA) {
			if(VDisplay == 1050) {
				ModeIndex = ModeIndex_1400x1050[Depth];
			}
		}
		break;
	case 1600:
		if(VDisplay == 1200) ModeIndex = ModeIndex_1600x1200[Depth];
		break;
	case 1680:
		if(VGAEngine == SIS_315_VGA) {
			if(VDisplay == 1050) ModeIndex = ModeIndex_1680x1050[Depth];
		}
		break;
	case 1920:
		if(VDisplay == 1440) ModeIndex = ModeIndex_1920x1440[Depth];
		else if(VGAEngine == SIS_315_VGA) {
			if(VDisplay == 1080) ModeIndex = ModeIndex_1920x1080[Depth];
		}
		break;
	case 2048:
		if(VDisplay == 1536) {
			if(VGAEngine == SIS_300_VGA) {
				ModeIndex = ModeIndex_300_2048x1536[Depth];
			} else {
				ModeIndex = ModeIndex_310_2048x1536[Depth];
			}
		}
		break;
   }

   return ModeIndex;
}