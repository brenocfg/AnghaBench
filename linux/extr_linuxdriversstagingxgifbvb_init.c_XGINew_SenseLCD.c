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
struct xgi_hw_device_info {unsigned short ulCRT2LCDType; } ;
struct vb_device_info {int /*<<< orphan*/  P3d4; } ;

/* Variables and functions */
#define  LCD_1024x600 135 
#define  LCD_1152x768 134 
#define  LCD_1152x864 133 
#define  LCD_1280x960 132 
#define  LCD_1920x1440 131 
#define  LCD_2048x1536 130 
#define  LCD_640x480 129 
#define  LCD_UNKNOWN 128 
 int /*<<< orphan*/  xgifb_reg_and_or (int /*<<< orphan*/ ,int,int,unsigned short) ; 

__attribute__((used)) static unsigned short XGINew_SenseLCD(struct xgi_hw_device_info
							*HwDeviceExtension,
				      struct vb_device_info *pVBInfo)
{
	unsigned short temp = HwDeviceExtension->ulCRT2LCDType;

	switch (HwDeviceExtension->ulCRT2LCDType) {
	case LCD_640x480:
	case LCD_1024x600:
	case LCD_1152x864:
	case LCD_1280x960:
	case LCD_1152x768:
	case LCD_1920x1440:
	case LCD_2048x1536:
		temp = 0; /* overwrite used ulCRT2LCDType */
		break;
	case LCD_UNKNOWN: /* unknown lcd, do nothing */
		return 0;
	}
	xgifb_reg_and_or(pVBInfo->P3d4, 0x36, 0xF0, temp);
	return 1;
}