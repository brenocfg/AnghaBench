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
struct snd_info_entry {struct snd_emu10k1* private_data; } ;
struct snd_info_buffer {int dummy; } ;
struct TYPE_5__ {scalar_t__ bytes; } ;
struct TYPE_6__ {TYPE_2__ etram_pages; int /*<<< orphan*/  itram_size; } ;
struct snd_emu10k1 {int* efx_voices_mask; scalar_t__ audigy; TYPE_3__ fx8010; TYPE_1__* card_capabilities; } ;
struct TYPE_4__ {scalar_t__ ecard; } ;

/* Variables and functions */
 int /*<<< orphan*/  A_FXRT1 ; 
 int /*<<< orphan*/  A_FXRT2 ; 
 int /*<<< orphan*/  FXRT ; 
 int NUM_G ; 
 unsigned int snd_emu10k1_ptr_read (struct snd_emu10k1*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snd_iprintf (struct snd_info_buffer*,char*,...) ; 

__attribute__((used)) static void snd_emu10k1_proc_read(struct snd_info_entry *entry, 
				  struct snd_info_buffer *buffer)
{
	/* FIXME - output names are in emufx.c too */
	static char *creative_outs[32] = {
		/* 00 */ "AC97 Left",
		/* 01 */ "AC97 Right",
		/* 02 */ "Optical IEC958 Left",
		/* 03 */ "Optical IEC958 Right",
		/* 04 */ "Center",
		/* 05 */ "LFE",
		/* 06 */ "Headphone Left",
		/* 07 */ "Headphone Right",
		/* 08 */ "Surround Left",
		/* 09 */ "Surround Right",
		/* 10 */ "PCM Capture Left",
		/* 11 */ "PCM Capture Right",
		/* 12 */ "MIC Capture",
		/* 13 */ "AC97 Surround Left",
		/* 14 */ "AC97 Surround Right",
		/* 15 */ "???",
		/* 16 */ "???",
		/* 17 */ "Analog Center",
		/* 18 */ "Analog LFE",
		/* 19 */ "???",
		/* 20 */ "???",
		/* 21 */ "???",
		/* 22 */ "???",
		/* 23 */ "???",
		/* 24 */ "???",
		/* 25 */ "???",
		/* 26 */ "???",
		/* 27 */ "???",
		/* 28 */ "???",
		/* 29 */ "???",
		/* 30 */ "???",
		/* 31 */ "???"
	};

	static char *audigy_outs[64] = {
		/* 00 */ "Digital Front Left",
		/* 01 */ "Digital Front Right",
		/* 02 */ "Digital Center",
		/* 03 */ "Digital LEF",
		/* 04 */ "Headphone Left",
		/* 05 */ "Headphone Right",
		/* 06 */ "Digital Rear Left",
		/* 07 */ "Digital Rear Right",
		/* 08 */ "Front Left",
		/* 09 */ "Front Right",
		/* 10 */ "Center",
		/* 11 */ "LFE",
		/* 12 */ "???",
		/* 13 */ "???",
		/* 14 */ "Rear Left",
		/* 15 */ "Rear Right",
		/* 16 */ "AC97 Front Left",
		/* 17 */ "AC97 Front Right",
		/* 18 */ "ADC Capture Left",
		/* 19 */ "ADC Capture Right",
		/* 20 */ "???",
		/* 21 */ "???",
		/* 22 */ "???",
		/* 23 */ "???",
		/* 24 */ "???",
		/* 25 */ "???",
		/* 26 */ "???",
		/* 27 */ "???",
		/* 28 */ "???",
		/* 29 */ "???",
		/* 30 */ "???",
		/* 31 */ "???",
		/* 32 */ "FXBUS2_0",
		/* 33 */ "FXBUS2_1",
		/* 34 */ "FXBUS2_2",
		/* 35 */ "FXBUS2_3",
		/* 36 */ "FXBUS2_4",
		/* 37 */ "FXBUS2_5",
		/* 38 */ "FXBUS2_6",
		/* 39 */ "FXBUS2_7",
		/* 40 */ "FXBUS2_8",
		/* 41 */ "FXBUS2_9",
		/* 42 */ "FXBUS2_10",
		/* 43 */ "FXBUS2_11",
		/* 44 */ "FXBUS2_12",
		/* 45 */ "FXBUS2_13",
		/* 46 */ "FXBUS2_14",
		/* 47 */ "FXBUS2_15",
		/* 48 */ "FXBUS2_16",
		/* 49 */ "FXBUS2_17",
		/* 50 */ "FXBUS2_18",
		/* 51 */ "FXBUS2_19",
		/* 52 */ "FXBUS2_20",
		/* 53 */ "FXBUS2_21",
		/* 54 */ "FXBUS2_22",
		/* 55 */ "FXBUS2_23",
		/* 56 */ "FXBUS2_24",
		/* 57 */ "FXBUS2_25",
		/* 58 */ "FXBUS2_26",
		/* 59 */ "FXBUS2_27",
		/* 60 */ "FXBUS2_28",
		/* 61 */ "FXBUS2_29",
		/* 62 */ "FXBUS2_30",
		/* 63 */ "FXBUS2_31"
	};

	struct snd_emu10k1 *emu = entry->private_data;
	unsigned int val, val1;
	int nefx = emu->audigy ? 64 : 32;
	char **outputs = emu->audigy ? audigy_outs : creative_outs;
	int idx;
	
	snd_iprintf(buffer, "EMU10K1\n\n");
	snd_iprintf(buffer, "Card                  : %s\n",
		    emu->audigy ? "Audigy" : (emu->card_capabilities->ecard ? "EMU APS" : "Creative"));
	snd_iprintf(buffer, "Internal TRAM (words) : 0x%x\n", emu->fx8010.itram_size);
	snd_iprintf(buffer, "External TRAM (words) : 0x%x\n", (int)emu->fx8010.etram_pages.bytes / 2);
	snd_iprintf(buffer, "\n");
	snd_iprintf(buffer, "Effect Send Routing   :\n");
	for (idx = 0; idx < NUM_G; idx++) {
		val = emu->audigy ?
			snd_emu10k1_ptr_read(emu, A_FXRT1, idx) :
			snd_emu10k1_ptr_read(emu, FXRT, idx);
		val1 = emu->audigy ?
			snd_emu10k1_ptr_read(emu, A_FXRT2, idx) :
			0;
		if (emu->audigy) {
			snd_iprintf(buffer, "Ch%i: A=%i, B=%i, C=%i, D=%i, ",
				idx,
				val & 0x3f,
				(val >> 8) & 0x3f,
				(val >> 16) & 0x3f,
				(val >> 24) & 0x3f);
			snd_iprintf(buffer, "E=%i, F=%i, G=%i, H=%i\n",
				val1 & 0x3f,
				(val1 >> 8) & 0x3f,
				(val1 >> 16) & 0x3f,
				(val1 >> 24) & 0x3f);
		} else {
			snd_iprintf(buffer, "Ch%i: A=%i, B=%i, C=%i, D=%i\n",
				idx,
				(val >> 16) & 0x0f,
				(val >> 20) & 0x0f,
				(val >> 24) & 0x0f,
				(val >> 28) & 0x0f);
		}
	}
	snd_iprintf(buffer, "\nCaptured FX Outputs   :\n");
	for (idx = 0; idx < nefx; idx++) {
		if (emu->efx_voices_mask[idx/32] & (1 << (idx%32)))
			snd_iprintf(buffer, "  Output %02i [%s]\n", idx, outputs[idx]);
	}
	snd_iprintf(buffer, "\nAll FX Outputs        :\n");
	for (idx = 0; idx < (emu->audigy ? 64 : 32); idx++)
		snd_iprintf(buffer, "  Output %02i [%s]\n", idx, outputs[idx]);
}