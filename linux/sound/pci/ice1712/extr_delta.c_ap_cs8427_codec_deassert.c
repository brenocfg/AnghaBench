#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int subvendor; } ;
struct snd_ice1712 {TYPE_1__ eeprom; } ;

/* Variables and functions */
 unsigned char ICE1712_DELTA_1010LT_CS ; 
 unsigned char ICE1712_DELTA_1010LT_CS_NONE ; 
 unsigned char ICE1712_DELTA_66E_CS_CS8427 ; 
 unsigned char ICE1712_DELTA_AP_CS_DIGITAL ; 
 int /*<<< orphan*/  ICE1712_IREG_GPIO_DATA ; 
#define  ICE1712_SUBDEVICE_AUDIOPHILE 133 
#define  ICE1712_SUBDEVICE_DELTA1010E 132 
#define  ICE1712_SUBDEVICE_DELTA1010LT 131 
#define  ICE1712_SUBDEVICE_DELTA410 130 
#define  ICE1712_SUBDEVICE_DELTA66E 129 
#define  ICE1712_SUBDEVICE_VX442 128 
 unsigned char ICE1712_VX442_CS_DIGITAL ; 
 int /*<<< orphan*/  snd_ice1712_write (struct snd_ice1712*,int /*<<< orphan*/ ,unsigned char) ; 

__attribute__((used)) static void ap_cs8427_codec_deassert(struct snd_ice1712 *ice, unsigned char tmp)
{
	switch (ice->eeprom.subvendor) {
	case ICE1712_SUBDEVICE_DELTA1010E:
	case ICE1712_SUBDEVICE_DELTA1010LT:
		tmp &= ~ICE1712_DELTA_1010LT_CS;
		tmp |= ICE1712_DELTA_1010LT_CS_NONE;
		break;
	case ICE1712_SUBDEVICE_AUDIOPHILE:
	case ICE1712_SUBDEVICE_DELTA410:
		tmp |= ICE1712_DELTA_AP_CS_DIGITAL;
		break;
	case ICE1712_SUBDEVICE_DELTA66E:
		tmp |= ICE1712_DELTA_66E_CS_CS8427;
		break;
	case ICE1712_SUBDEVICE_VX442:
		tmp |= ICE1712_VX442_CS_DIGITAL;
		break;
	}
	snd_ice1712_write(ice, ICE1712_IREG_GPIO_DATA, tmp);
}