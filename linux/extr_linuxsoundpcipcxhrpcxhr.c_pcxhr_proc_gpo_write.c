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
struct snd_pcxhr {struct pcxhr_mgr* mgr; } ;
struct snd_info_entry {struct snd_pcxhr* private_data; } ;
struct snd_info_buffer {int dummy; } ;
struct pcxhr_mgr {int dsp_loaded; } ;
typedef  int /*<<< orphan*/  line ;

/* Variables and functions */
 int PCXHR_FIRMWARE_DSP_MAIN_INDEX ; 
 int /*<<< orphan*/  hr222_write_gpo (struct pcxhr_mgr*,int) ; 
 int /*<<< orphan*/  snd_info_get_line (struct snd_info_buffer*,char*,int) ; 
 int sscanf (char*,char*,int*) ; 

__attribute__((used)) static void pcxhr_proc_gpo_write(struct snd_info_entry *entry,
				 struct snd_info_buffer *buffer)
{
	struct snd_pcxhr *chip = entry->private_data;
	struct pcxhr_mgr *mgr = chip->mgr;
	char line[64];
	int value;
	/* commands available when embedded DSP is running */
	if (!(mgr->dsp_loaded & (1 << PCXHR_FIRMWARE_DSP_MAIN_INDEX)))
		return;
	while (!snd_info_get_line(buffer, line, sizeof(line))) {
		if (sscanf(line, "GPO: 0x%x", &value) != 1)
			continue;
		hr222_write_gpo(mgr, value);	/* GP0 */
	}
}