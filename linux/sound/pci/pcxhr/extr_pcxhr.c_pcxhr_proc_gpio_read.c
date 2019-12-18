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

/* Variables and functions */
 int PCXHR_FIRMWARE_DSP_MAIN_INDEX ; 
 int /*<<< orphan*/  hr222_read_gpio (struct pcxhr_mgr*,int,int*) ; 
 int /*<<< orphan*/  snd_iprintf (struct snd_info_buffer*,char*,...) ; 

__attribute__((used)) static void pcxhr_proc_gpio_read(struct snd_info_entry *entry,
				 struct snd_info_buffer *buffer)
{
	struct snd_pcxhr *chip = entry->private_data;
	struct pcxhr_mgr *mgr = chip->mgr;
	/* commands available when embedded DSP is running */
	if (mgr->dsp_loaded & (1 << PCXHR_FIRMWARE_DSP_MAIN_INDEX)) {
		/* gpio ports on stereo boards only available */
		int value = 0;
		hr222_read_gpio(mgr, 1, &value);	/* GPI */
		snd_iprintf(buffer, "GPI: 0x%x\n", value);
		hr222_read_gpio(mgr, 0, &value);	/* GP0 */
		snd_iprintf(buffer, "GPO: 0x%x\n", value);
	} else
		snd_iprintf(buffer, "no firmware loaded\n");
	snd_iprintf(buffer, "\n");
}