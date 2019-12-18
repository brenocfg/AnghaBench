#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct snd_info_entry {struct snd_ac97* private_data; } ;
struct snd_info_buffer {int dummy; } ;
struct TYPE_3__ {int* unchained; int* chained; scalar_t__* id; } ;
struct TYPE_4__ {TYPE_1__ ad18xx; } ;
struct snd_ac97 {int id; int /*<<< orphan*/  page_mutex; TYPE_2__ spec; } ;

/* Variables and functions */
 int /*<<< orphan*/  AC97_AD_SERIAL_CFG ; 
 int AC97_ID_AD1881 ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_ac97_proc_read_main (struct snd_ac97*,struct snd_info_buffer*,int) ; 
 int /*<<< orphan*/  snd_ac97_update_bits (struct snd_ac97*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  snd_iprintf (struct snd_info_buffer*,char*,...) ; 

__attribute__((used)) static void snd_ac97_proc_read(struct snd_info_entry *entry, struct snd_info_buffer *buffer)
{
	struct snd_ac97 *ac97 = entry->private_data;
	
	mutex_lock(&ac97->page_mutex);
	if ((ac97->id & 0xffffff40) == AC97_ID_AD1881) {	// Analog Devices AD1881/85/86
		int idx;
		for (idx = 0; idx < 3; idx++)
			if (ac97->spec.ad18xx.id[idx]) {
				/* select single codec */
				snd_ac97_update_bits(ac97, AC97_AD_SERIAL_CFG, 0x7000,
						     ac97->spec.ad18xx.unchained[idx] | ac97->spec.ad18xx.chained[idx]);
				snd_ac97_proc_read_main(ac97, buffer, idx);
				snd_iprintf(buffer, "\n\n");
			}
		/* select all codecs */
		snd_ac97_update_bits(ac97, AC97_AD_SERIAL_CFG, 0x7000, 0x7000);
		
		snd_iprintf(buffer, "\nAD18XX configuration\n");
		snd_iprintf(buffer, "Unchained        : 0x%04x,0x%04x,0x%04x\n",
			ac97->spec.ad18xx.unchained[0],
			ac97->spec.ad18xx.unchained[1],
			ac97->spec.ad18xx.unchained[2]);
		snd_iprintf(buffer, "Chained          : 0x%04x,0x%04x,0x%04x\n",
			ac97->spec.ad18xx.chained[0],
			ac97->spec.ad18xx.chained[1],
			ac97->spec.ad18xx.chained[2]);
	} else {
		snd_ac97_proc_read_main(ac97, buffer, 0);
	}
	mutex_unlock(&ac97->page_mutex);
}