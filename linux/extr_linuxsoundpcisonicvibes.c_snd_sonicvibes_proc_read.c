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
struct sonicvibes {int srs_space; int srs_center; int wave_source; unsigned char mpu_switch; } ;
struct snd_info_entry {struct sonicvibes* private_data; } ;
struct snd_info_buffer {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  snd_iprintf (struct snd_info_buffer*,char*,char*) ; 

__attribute__((used)) static void snd_sonicvibes_proc_read(struct snd_info_entry *entry, 
				     struct snd_info_buffer *buffer)
{
	struct sonicvibes *sonic = entry->private_data;
	unsigned char tmp;

	tmp = sonic->srs_space & 0x0f;
	snd_iprintf(buffer, "SRS 3D           : %s\n",
		    sonic->srs_space & 0x80 ? "off" : "on");
	snd_iprintf(buffer, "SRS Space        : %s\n",
		    tmp == 0x00 ? "100%" :
		    tmp == 0x01 ? "75%" :
		    tmp == 0x02 ? "50%" :
		    tmp == 0x03 ? "25%" : "0%");
	tmp = sonic->srs_center & 0x0f;
	snd_iprintf(buffer, "SRS Center       : %s\n",
		    tmp == 0x00 ? "100%" :
		    tmp == 0x01 ? "75%" :
		    tmp == 0x02 ? "50%" :
		    tmp == 0x03 ? "25%" : "0%");
	tmp = sonic->wave_source & 0x03;
	snd_iprintf(buffer, "WaveTable Source : %s\n",
		    tmp == 0x00 ? "on-board ROM" :
		    tmp == 0x01 ? "PCI bus" : "on-board ROM + PCI bus");
	tmp = sonic->mpu_switch;
	snd_iprintf(buffer, "Onboard synth    : %s\n", tmp & 0x01 ? "on" : "off");
	snd_iprintf(buffer, "Ext. Rx to synth : %s\n", tmp & 0x02 ? "on" : "off");
	snd_iprintf(buffer, "MIDI to ext. Tx  : %s\n", tmp & 0x04 ? "on" : "off");
}