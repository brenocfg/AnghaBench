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
typedef  int u32 ;
struct snd_info_entry {struct snd_emu10k1* private_data; } ;
struct snd_info_buffer {int dummy; } ;
struct snd_emu10k1 {TYPE_1__* card_capabilities; } ;
struct TYPE_2__ {scalar_t__ emu_model; } ;

/* Variables and functions */
 int /*<<< orphan*/  CDCS ; 
 int /*<<< orphan*/  CDSRCS ; 
 int /*<<< orphan*/  GPSCS ; 
 int /*<<< orphan*/  GPSRCS ; 
 int SRCS_ESTSAMPLERATE ; 
 int SRCS_RATELOCKED ; 
 int /*<<< orphan*/  ZVSRCS ; 
 int /*<<< orphan*/  snd_emu1010_fpga_read (struct snd_emu10k1*,int,int*) ; 
 int /*<<< orphan*/  snd_emu10k1_proc_spdif_status (struct snd_emu10k1*,struct snd_info_buffer*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int snd_emu10k1_ptr_read (struct snd_emu10k1*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_iprintf (struct snd_info_buffer*,char*,...) ; 
 int val ; 

__attribute__((used)) static void snd_emu10k1_proc_spdif_read(struct snd_info_entry *entry, 
				  struct snd_info_buffer *buffer)
{
	struct snd_emu10k1 *emu = entry->private_data;
	u32 value;
	u32 value2;
	u32 rate;

	if (emu->card_capabilities->emu_model) {
		snd_emu1010_fpga_read(emu, 0x38, &value);
		if ((value & 0x1) == 0) {
			snd_emu1010_fpga_read(emu, 0x2a, &value);
			snd_emu1010_fpga_read(emu, 0x2b, &value2);
			rate = 0x1770000 / (((value << 5) | value2)+1);	
			snd_iprintf(buffer, "ADAT Locked : %u\n", rate);
		} else {
			snd_iprintf(buffer, "ADAT Unlocked\n");
		}
		snd_emu1010_fpga_read(emu, 0x20, &value);
		if ((value & 0x4) == 0) {
			snd_emu1010_fpga_read(emu, 0x28, &value);
			snd_emu1010_fpga_read(emu, 0x29, &value2);
			rate = 0x1770000 / (((value << 5) | value2)+1);	
			snd_iprintf(buffer, "SPDIF Locked : %d\n", rate);
		} else {
			snd_iprintf(buffer, "SPDIF Unlocked\n");
		}
	} else {
		snd_emu10k1_proc_spdif_status(emu, buffer, "CD-ROM S/PDIF In", CDCS, CDSRCS);
		snd_emu10k1_proc_spdif_status(emu, buffer, "Optical or Coax S/PDIF In", GPSCS, GPSRCS);
	}
#if 0
	val = snd_emu10k1_ptr_read(emu, ZVSRCS, 0);
	snd_iprintf(buffer, "\nZoomed Video\n");
	snd_iprintf(buffer, "Rate Locked           : %s\n", val & SRCS_RATELOCKED ? "on" : "off");
	snd_iprintf(buffer, "Estimated Sample Rate : 0x%x\n", val & SRCS_ESTSAMPLERATE);
#endif
}