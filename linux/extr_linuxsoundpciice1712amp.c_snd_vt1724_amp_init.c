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
struct TYPE_2__ {scalar_t__ subvendor; } ;
struct snd_ice1712 {int num_total_dacs; int num_total_adcs; TYPE_1__ eeprom; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (unsigned short const*) ; 
 scalar_t__ VT1724_SUBDEVICE_AV710 ; 
#define  WM_ATTEN_L 131 
#define  WM_ATTEN_R 130 
#define  WM_DAC_CTRL 129 
#define  WM_INT_CTRL 128 
 int /*<<< orphan*/  wm_put (struct snd_ice1712*,unsigned short const,unsigned short const) ; 

__attribute__((used)) static int snd_vt1724_amp_init(struct snd_ice1712 *ice)
{
	static const unsigned short wm_inits[] = {
		WM_ATTEN_L,	0x0000,	/* 0 db */
		WM_ATTEN_R,	0x0000,	/* 0 db */
		WM_DAC_CTRL,	0x0008,	/* 24bit I2S */
		WM_INT_CTRL,	0x0001, /* 24bit I2S */	
	};

	unsigned int i;

	/* only use basic functionality for now */

	/* VT1616 6ch codec connected to PSDOUT0 using packed mode */
	ice->num_total_dacs = 6;
	ice->num_total_adcs = 2;

	/* Chaintech AV-710 has another WM8728 codec connected to PSDOUT4
	   (shared with the SPDIF output). Mixer control for this codec
	   is not yet supported. */
	if (ice->eeprom.subvendor == VT1724_SUBDEVICE_AV710) {
		for (i = 0; i < ARRAY_SIZE(wm_inits); i += 2)
			wm_put(ice, wm_inits[i], wm_inits[i+1]);
	}

	return 0;
}