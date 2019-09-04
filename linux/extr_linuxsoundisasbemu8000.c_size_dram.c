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
struct snd_emu8000 {int dram_checked; int mem_size; int /*<<< orphan*/  port1; } ;

/* Variables and functions */
 scalar_t__ EMU8000_DRAM_OFFSET ; 
 int EMU8000_MAX_DRAM ; 
 int /*<<< orphan*/  EMU8000_RAM_CLOSE ; 
 int /*<<< orphan*/  EMU8000_RAM_READ ; 
 int /*<<< orphan*/  EMU8000_RAM_WRITE ; 
 int /*<<< orphan*/  EMU8000_SMALR_WRITE (struct snd_emu8000*,scalar_t__) ; 
 int EMU8000_SMALW_READ (struct snd_emu8000*) ; 
 int /*<<< orphan*/  EMU8000_SMALW_WRITE (struct snd_emu8000*,scalar_t__) ; 
 scalar_t__ EMU8000_SMLD_READ (struct snd_emu8000*) ; 
 int /*<<< orphan*/  EMU8000_SMLD_WRITE (struct snd_emu8000*,scalar_t__) ; 
 scalar_t__ UNIQUE_ID1 ; 
 scalar_t__ UNIQUE_ID2 ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  schedule_timeout_interruptible (int) ; 
 scalar_t__ signal_pending (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_emu8000_dma_chan (struct snd_emu8000*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_emu8000_init_fm (struct snd_emu8000*) ; 
 int /*<<< orphan*/  snd_emu8000_read_wait (struct snd_emu8000*) ; 
 int /*<<< orphan*/  snd_emu8000_write_wait (struct snd_emu8000*) ; 

__attribute__((used)) static void
size_dram(struct snd_emu8000 *emu)
{
	int i, size;

	if (emu->dram_checked)
		return;

	size = 0;

	/* write out a magic number */
	snd_emu8000_dma_chan(emu, 0, EMU8000_RAM_WRITE);
	snd_emu8000_dma_chan(emu, 1, EMU8000_RAM_READ);
	EMU8000_SMALW_WRITE(emu, EMU8000_DRAM_OFFSET);
	EMU8000_SMLD_WRITE(emu, UNIQUE_ID1);
	snd_emu8000_init_fm(emu); /* This must really be here and not 2 lines back even */
	snd_emu8000_write_wait(emu);

	/*
	 * Detect first 512 KiB.  If a write succeeds at the beginning of a
	 * 512 KiB page we assume that the whole page is there.
	 */
	EMU8000_SMALR_WRITE(emu, EMU8000_DRAM_OFFSET);
	EMU8000_SMLD_READ(emu); /* discard stale data  */
	if (EMU8000_SMLD_READ(emu) != UNIQUE_ID1)
		goto skip_detect;   /* No RAM */
	snd_emu8000_read_wait(emu);

	for (size = 512 * 1024; size < EMU8000_MAX_DRAM; size += 512 * 1024) {

		/* Write a unique data on the test address.
		 * if the address is out of range, the data is written on
		 * 0x200000(=EMU8000_DRAM_OFFSET).  Then the id word is
		 * changed by this data.
		 */
		/*snd_emu8000_dma_chan(emu, 0, EMU8000_RAM_WRITE);*/
		EMU8000_SMALW_WRITE(emu, EMU8000_DRAM_OFFSET + (size>>1));
		EMU8000_SMLD_WRITE(emu, UNIQUE_ID2);
		snd_emu8000_write_wait(emu);

		/*
		 * read the data on the just written DRAM address
		 * if not the same then we have reached the end of ram.
		 */
		/*snd_emu8000_dma_chan(emu, 0, EMU8000_RAM_READ);*/
		EMU8000_SMALR_WRITE(emu, EMU8000_DRAM_OFFSET + (size>>1));
		/*snd_emu8000_read_wait(emu);*/
		EMU8000_SMLD_READ(emu); /* discard stale data  */
		if (EMU8000_SMLD_READ(emu) != UNIQUE_ID2)
			break; /* no memory at this address */
		snd_emu8000_read_wait(emu);

		/*
		 * If it is the same it could be that the address just
		 * wraps back to the beginning; so check to see if the
		 * initial value has been overwritten.
		 */
		EMU8000_SMALR_WRITE(emu, EMU8000_DRAM_OFFSET);
		EMU8000_SMLD_READ(emu); /* discard stale data  */
		if (EMU8000_SMLD_READ(emu) != UNIQUE_ID1)
			break; /* we must have wrapped around */
		snd_emu8000_read_wait(emu);

		/* Otherwise, it's valid memory. */
	}

skip_detect:
	/* wait until FULL bit in SMAxW register is false */
	for (i = 0; i < 10000; i++) {
		if ((EMU8000_SMALW_READ(emu) & 0x80000000) == 0)
			break;
		schedule_timeout_interruptible(1);
		if (signal_pending(current))
			break;
	}
	snd_emu8000_dma_chan(emu, 0, EMU8000_RAM_CLOSE);
	snd_emu8000_dma_chan(emu, 1, EMU8000_RAM_CLOSE);

	pr_info("EMU8000 [0x%lx]: %d KiB on-board DRAM detected\n",
		    emu->port1, size/1024);

	emu->mem_size = size;
	emu->dram_checked = 1;
}