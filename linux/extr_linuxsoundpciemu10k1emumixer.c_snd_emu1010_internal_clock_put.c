#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct snd_kcontrol {int dummy; } ;
struct TYPE_6__ {unsigned int internal_clock; } ;
struct snd_emu10k1 {TYPE_3__ emu1010; } ;
struct TYPE_4__ {unsigned int* item; } ;
struct TYPE_5__ {TYPE_1__ enumerated; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  EMU_HANA_DEFCLOCK ; 
 int EMU_HANA_DEFCLOCK_44_1K ; 
 int EMU_HANA_DEFCLOCK_48K ; 
 int /*<<< orphan*/  EMU_HANA_DOCK_LEDS_2 ; 
 int EMU_HANA_DOCK_LEDS_2_44K ; 
 int EMU_HANA_DOCK_LEDS_2_48K ; 
 int EMU_HANA_DOCK_LEDS_2_EXT ; 
 int EMU_HANA_DOCK_LEDS_2_LOCK ; 
 int /*<<< orphan*/  EMU_HANA_UNMUTE ; 
 int /*<<< orphan*/  EMU_HANA_WCLOCK ; 
 int EMU_HANA_WCLOCK_1X ; 
 int EMU_HANA_WCLOCK_HANA_ADAT_IN ; 
 int EMU_HANA_WCLOCK_HANA_SPDIF_IN ; 
 int EMU_HANA_WCLOCK_INT_44_1K ; 
 int EMU_HANA_WCLOCK_INT_48K ; 
 int EMU_MUTE ; 
 int EMU_UNMUTE ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  snd_emu1010_fpga_write (struct snd_emu10k1*,int /*<<< orphan*/ ,int) ; 
 struct snd_emu10k1* snd_kcontrol_chip (struct snd_kcontrol*) ; 

__attribute__((used)) static int snd_emu1010_internal_clock_put(struct snd_kcontrol *kcontrol,
					struct snd_ctl_elem_value *ucontrol)
{
	struct snd_emu10k1 *emu = snd_kcontrol_chip(kcontrol);
	unsigned int val;
	int change = 0;

	val = ucontrol->value.enumerated.item[0] ;
	/* Limit: uinfo->value.enumerated.items = 4; */
	if (val >= 4)
		return -EINVAL;
	change = (emu->emu1010.internal_clock != val);
	if (change) {
		emu->emu1010.internal_clock = val;
		switch (val) {
		case 0:
			/* 44100 */
			/* Mute all */
			snd_emu1010_fpga_write(emu, EMU_HANA_UNMUTE, EMU_MUTE );
			/* Default fallback clock 48kHz */
			snd_emu1010_fpga_write(emu, EMU_HANA_DEFCLOCK, EMU_HANA_DEFCLOCK_44_1K );
			/* Word Clock source, Internal 44.1kHz x1 */
			snd_emu1010_fpga_write(emu, EMU_HANA_WCLOCK,
			EMU_HANA_WCLOCK_INT_44_1K | EMU_HANA_WCLOCK_1X );
			/* Set LEDs on Audio Dock */
			snd_emu1010_fpga_write(emu, EMU_HANA_DOCK_LEDS_2,
				EMU_HANA_DOCK_LEDS_2_44K | EMU_HANA_DOCK_LEDS_2_LOCK );
			/* Allow DLL to settle */
			msleep(10);
			/* Unmute all */
			snd_emu1010_fpga_write(emu, EMU_HANA_UNMUTE, EMU_UNMUTE );
			break;
		case 1:
			/* 48000 */
			/* Mute all */
			snd_emu1010_fpga_write(emu, EMU_HANA_UNMUTE, EMU_MUTE );
			/* Default fallback clock 48kHz */
			snd_emu1010_fpga_write(emu, EMU_HANA_DEFCLOCK, EMU_HANA_DEFCLOCK_48K );
			/* Word Clock source, Internal 48kHz x1 */
			snd_emu1010_fpga_write(emu, EMU_HANA_WCLOCK,
				EMU_HANA_WCLOCK_INT_48K | EMU_HANA_WCLOCK_1X );
			/* Set LEDs on Audio Dock */
			snd_emu1010_fpga_write(emu, EMU_HANA_DOCK_LEDS_2,
				EMU_HANA_DOCK_LEDS_2_48K | EMU_HANA_DOCK_LEDS_2_LOCK );
			/* Allow DLL to settle */
			msleep(10);
			/* Unmute all */
			snd_emu1010_fpga_write(emu, EMU_HANA_UNMUTE, EMU_UNMUTE );
			break;
			
		case 2: /* Take clock from S/PDIF IN */
			/* Mute all */
			snd_emu1010_fpga_write(emu, EMU_HANA_UNMUTE, EMU_MUTE );
			/* Default fallback clock 48kHz */
			snd_emu1010_fpga_write(emu, EMU_HANA_DEFCLOCK, EMU_HANA_DEFCLOCK_48K );
			/* Word Clock source, sync to S/PDIF input */
			snd_emu1010_fpga_write(emu, EMU_HANA_WCLOCK,
				EMU_HANA_WCLOCK_HANA_SPDIF_IN | EMU_HANA_WCLOCK_1X );
			/* Set LEDs on Audio Dock */
			snd_emu1010_fpga_write(emu, EMU_HANA_DOCK_LEDS_2,
				EMU_HANA_DOCK_LEDS_2_EXT | EMU_HANA_DOCK_LEDS_2_LOCK );
			/* FIXME: We should set EMU_HANA_DOCK_LEDS_2_LOCK only when clock signal is present and valid */	
			/* Allow DLL to settle */
			msleep(10);
			/* Unmute all */
			snd_emu1010_fpga_write(emu, EMU_HANA_UNMUTE, EMU_UNMUTE );
			break;
		
		case 3: 			
			/* Take clock from ADAT IN */
			/* Mute all */
			snd_emu1010_fpga_write(emu, EMU_HANA_UNMUTE, EMU_MUTE );
			/* Default fallback clock 48kHz */
			snd_emu1010_fpga_write(emu, EMU_HANA_DEFCLOCK, EMU_HANA_DEFCLOCK_48K );
			/* Word Clock source, sync to ADAT input */
			snd_emu1010_fpga_write(emu, EMU_HANA_WCLOCK,
				EMU_HANA_WCLOCK_HANA_ADAT_IN | EMU_HANA_WCLOCK_1X );
			/* Set LEDs on Audio Dock */
			snd_emu1010_fpga_write(emu, EMU_HANA_DOCK_LEDS_2, EMU_HANA_DOCK_LEDS_2_EXT | EMU_HANA_DOCK_LEDS_2_LOCK );
			/* FIXME: We should set EMU_HANA_DOCK_LEDS_2_LOCK only when clock signal is present and valid */	
			/* Allow DLL to settle */
			msleep(10);
			/*   Unmute all */
			snd_emu1010_fpga_write(emu, EMU_HANA_UNMUTE, EMU_UNMUTE );
			 
			
			break;		
		}
	}
        return change;
}