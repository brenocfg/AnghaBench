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
struct snd_info_entry {struct cs4281* private_data; } ;
struct snd_info_buffer {int dummy; } ;
struct cs4281 {int /*<<< orphan*/  spurious_dtc_irq; int /*<<< orphan*/  spurious_dhtc_irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  snd_iprintf (struct snd_info_buffer*,char*,...) ; 

__attribute__((used)) static void snd_cs4281_proc_read(struct snd_info_entry *entry, 
				  struct snd_info_buffer *buffer)
{
	struct cs4281 *chip = entry->private_data;

	snd_iprintf(buffer, "Cirrus Logic CS4281\n\n");
	snd_iprintf(buffer, "Spurious half IRQs   : %u\n", chip->spurious_dhtc_irq);
	snd_iprintf(buffer, "Spurious end IRQs    : %u\n", chip->spurious_dtc_irq);
}