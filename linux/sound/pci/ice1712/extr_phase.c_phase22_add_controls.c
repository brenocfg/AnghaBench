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
#define  VT1724_SUBDEVICE_PHASE22 129 
#define  VT1724_SUBDEVICE_TS22 128 
 int snd_ice1712_akm4xxx_build_controls (struct snd_ice1712*) ; 

__attribute__((used)) static int phase22_add_controls(struct snd_ice1712 *ice)
{
	int err = 0;

	switch (ice->eeprom.subvendor) {
	case VT1724_SUBDEVICE_PHASE22:
	case VT1724_SUBDEVICE_TS22:
		err = snd_ice1712_akm4xxx_build_controls(ice);
		if (err < 0)
			return err;
	}
	return 0;
}