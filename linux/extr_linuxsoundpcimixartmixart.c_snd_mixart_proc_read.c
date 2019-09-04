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
typedef  int u32 ;
struct snd_mixart {int chip_idx; TYPE_1__* mgr; } ;
struct snd_info_entry {struct snd_mixart* private_data; } ;
struct snd_info_buffer {int dummy; } ;
struct TYPE_2__ {int dsp_loaded; int board_type; } ;

/* Variables and functions */
#define  MIXART_DAUGHTER_TYPE_AES 130 
#define  MIXART_DAUGHTER_TYPE_COBRANET 129 
#define  MIXART_DAUGHTER_TYPE_NONE 128 
 int /*<<< orphan*/  MIXART_MEM (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int MIXART_MOTHERBOARD_ELF_INDEX ; 
 int /*<<< orphan*/  MIXART_PSEUDOREG_PERF_INTERR_LOAD_OFFSET ; 
 int /*<<< orphan*/  MIXART_PSEUDOREG_PERF_MAILBX_LOAD_OFFSET ; 
 int /*<<< orphan*/  MIXART_PSEUDOREG_PERF_STREAM_LOAD_OFFSET ; 
 int /*<<< orphan*/  MIXART_PSEUDOREG_PERF_SYSTEM_LOAD_OFFSET ; 
 int readl_be (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_iprintf (struct snd_info_buffer*,char*,...) ; 

__attribute__((used)) static void snd_mixart_proc_read(struct snd_info_entry *entry, 
                                 struct snd_info_buffer *buffer)
{
	struct snd_mixart *chip = entry->private_data;        
	u32 ref; 

	snd_iprintf(buffer, "Digigram miXart (alsa card %d)\n\n", chip->chip_idx);

	/* stats available when embedded OS is running */
	if (chip->mgr->dsp_loaded & ( 1 << MIXART_MOTHERBOARD_ELF_INDEX)) {
		snd_iprintf(buffer, "- hardware -\n");
		switch (chip->mgr->board_type ) {
		case MIXART_DAUGHTER_TYPE_NONE     : snd_iprintf(buffer, "\tmiXart8 (no daughter board)\n\n"); break;
		case MIXART_DAUGHTER_TYPE_AES      : snd_iprintf(buffer, "\tmiXart8 AES/EBU\n\n"); break;
		case MIXART_DAUGHTER_TYPE_COBRANET : snd_iprintf(buffer, "\tmiXart8 Cobranet\n\n"); break;
		default:                             snd_iprintf(buffer, "\tUNKNOWN!\n\n"); break;
		}

		snd_iprintf(buffer, "- system load -\n");	 

		/* get perf reference */

		ref = readl_be( MIXART_MEM( chip->mgr, MIXART_PSEUDOREG_PERF_SYSTEM_LOAD_OFFSET));

		if (ref) {
			u32 mailbox   = 100 * readl_be( MIXART_MEM( chip->mgr, MIXART_PSEUDOREG_PERF_MAILBX_LOAD_OFFSET)) / ref;
			u32 streaming = 100 * readl_be( MIXART_MEM( chip->mgr, MIXART_PSEUDOREG_PERF_STREAM_LOAD_OFFSET)) / ref;
			u32 interr    = 100 * readl_be( MIXART_MEM( chip->mgr, MIXART_PSEUDOREG_PERF_INTERR_LOAD_OFFSET)) / ref;

			snd_iprintf(buffer, "\tstreaming          : %d\n", streaming);
			snd_iprintf(buffer, "\tmailbox            : %d\n", mailbox);
			snd_iprintf(buffer, "\tinterrupts handling : %d\n\n", interr);
		}
	} /* endif elf loaded */
}