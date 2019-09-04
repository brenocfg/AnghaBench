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
typedef  int u32 ;
struct snd_info_entry {struct snd_ca0106* private_data; } ;
struct snd_info_buffer {int dummy; } ;
struct snd_ca0106 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SAMPLE_RATE_TRACKER_STATUS ; 
 int /*<<< orphan*/  SPDIF_INPUT_STATUS ; 
 int /*<<< orphan*/  snd_ca0106_proc_dump_iec958 (struct snd_info_buffer*,int) ; 
 int snd_ca0106_ptr_read (struct snd_ca0106*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_iprintf (struct snd_info_buffer*,char*,...) ; 

__attribute__((used)) static void snd_ca0106_proc_iec958(struct snd_info_entry *entry, 
				       struct snd_info_buffer *buffer)
{
	struct snd_ca0106 *emu = entry->private_data;
	u32 value;

        value = snd_ca0106_ptr_read(emu, SAMPLE_RATE_TRACKER_STATUS, 0);
	snd_iprintf(buffer, "Status: %s, %s, %s\n",
		  (value & 0x100000) ? "Rate Locked" : "Not Rate Locked",
		  (value & 0x200000) ? "SPDIF Locked" : "No SPDIF Lock",
		  (value & 0x400000) ? "Audio Valid" : "No valid audio" );
	snd_iprintf(buffer, "Estimated sample rate: %u\n", 
		  ((value & 0xfffff) * 48000) / 0x8000 );
	if (value & 0x200000) {
		snd_iprintf(buffer, "IEC958/SPDIF input status:\n");
        	value = snd_ca0106_ptr_read(emu, SPDIF_INPUT_STATUS, 0);
		snd_ca0106_proc_dump_iec958(buffer, value);
	}

	snd_iprintf(buffer, "\n");
}