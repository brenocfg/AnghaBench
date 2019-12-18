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
struct snd_info_entry {struct snd_ak4531* private_data; } ;
struct snd_info_buffer {int dummy; } ;
struct snd_ak4531 {int* regs; } ;

/* Variables and functions */
 size_t AK4531_AD_IN ; 
 size_t AK4531_MIC_GAIN ; 
 int /*<<< orphan*/  snd_iprintf (struct snd_info_buffer*,char*,...) ; 

__attribute__((used)) static void snd_ak4531_proc_read(struct snd_info_entry *entry, 
				 struct snd_info_buffer *buffer)
{
	struct snd_ak4531 *ak4531 = entry->private_data;

	snd_iprintf(buffer, "Asahi Kasei AK4531\n\n");
	snd_iprintf(buffer, "Recording source   : %s\n"
		    "MIC gain           : %s\n",
		    ak4531->regs[AK4531_AD_IN] & 1 ? "external" : "mixer",
		    ak4531->regs[AK4531_MIC_GAIN] & 1 ? "+30dB" : "+0dB");
}