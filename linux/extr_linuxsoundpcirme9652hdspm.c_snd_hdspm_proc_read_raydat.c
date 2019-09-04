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
struct snd_info_entry {struct hdspm* private_data; } ;
struct snd_info_buffer {int dummy; } ;
struct hdspm {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HDSPM_RD_STATUS_1 ; 
 int /*<<< orphan*/  HDSPM_RD_STATUS_2 ; 
 int /*<<< orphan*/  HDSPM_RD_STATUS_3 ; 
 int /*<<< orphan*/  hdspm_get_system_sample_rate (struct hdspm*) ; 
 unsigned int hdspm_read (struct hdspm*,int /*<<< orphan*/ ) ; 
 scalar_t__ hdspm_system_clock_mode (struct hdspm*) ; 
 int /*<<< orphan*/  snd_iprintf (struct snd_info_buffer*,char*,...) ; 
 int /*<<< orphan*/ * texts_freq ; 

__attribute__((used)) static void
snd_hdspm_proc_read_raydat(struct snd_info_entry *entry,
			 struct snd_info_buffer *buffer)
{
	struct hdspm *hdspm = entry->private_data;
	unsigned int status1, status2, status3, i;
	unsigned int lock, sync;

	status1 = hdspm_read(hdspm, HDSPM_RD_STATUS_1); /* s1 */
	status2 = hdspm_read(hdspm, HDSPM_RD_STATUS_2); /* freq */
	status3 = hdspm_read(hdspm, HDSPM_RD_STATUS_3); /* s2 */

	snd_iprintf(buffer, "STATUS1: 0x%08x\n", status1);
	snd_iprintf(buffer, "STATUS2: 0x%08x\n", status2);
	snd_iprintf(buffer, "STATUS3: 0x%08x\n", status3);


	snd_iprintf(buffer, "\n*** CLOCK MODE\n\n");

	snd_iprintf(buffer, "Clock mode      : %s\n",
		(hdspm_system_clock_mode(hdspm) == 0) ? "master" : "slave");
	snd_iprintf(buffer, "System frequency: %d Hz\n",
		hdspm_get_system_sample_rate(hdspm));

	snd_iprintf(buffer, "\n*** INPUT STATUS\n\n");

	lock = 0x1;
	sync = 0x100;

	for (i = 0; i < 8; i++) {
		snd_iprintf(buffer, "s1_input %d: Lock %d, Sync %d, Freq %s\n",
				i,
				(status1 & lock) ? 1 : 0,
				(status1 & sync) ? 1 : 0,
				texts_freq[(status2 >> (i * 4)) & 0xF]);

		lock = lock<<1;
		sync = sync<<1;
	}

	snd_iprintf(buffer, "WC input: Lock %d, Sync %d, Freq %s\n",
			(status1 & 0x1000000) ? 1 : 0,
			(status1 & 0x2000000) ? 1 : 0,
			texts_freq[(status1 >> 16) & 0xF]);

	snd_iprintf(buffer, "TCO input: Lock %d, Sync %d, Freq %s\n",
			(status1 & 0x4000000) ? 1 : 0,
			(status1 & 0x8000000) ? 1 : 0,
			texts_freq[(status1 >> 20) & 0xF]);

	snd_iprintf(buffer, "SYNC IN: Lock %d, Sync %d, Freq %s\n",
			(status3 & 0x400) ? 1 : 0,
			(status3 & 0x800) ? 1 : 0,
			texts_freq[(status2 >> 12) & 0xF]);

}