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
struct via82xx_modem {scalar_t__ port; TYPE_1__* card; } ;
struct snd_info_entry {struct via82xx_modem* private_data; } ;
struct snd_info_buffer {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  longname; } ;

/* Variables and functions */
 int /*<<< orphan*/  inl (scalar_t__) ; 
 int /*<<< orphan*/  snd_iprintf (struct snd_info_buffer*,char*,int,...) ; 

__attribute__((used)) static void snd_via82xx_proc_read(struct snd_info_entry *entry, struct snd_info_buffer *buffer)
{
	struct via82xx_modem *chip = entry->private_data;
	int i;
	
	snd_iprintf(buffer, "%s\n\n", chip->card->longname);
	for (i = 0; i < 0xa0; i += 4) {
		snd_iprintf(buffer, "%02x: %08x\n", i, inl(chip->port + i));
	}
}