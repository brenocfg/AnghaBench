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
typedef  int u16 ;
struct snd_msnd {int play_sample_size; int play_channels; int play_sample_rate; scalar_t__ SMA; scalar_t__ DSPQ; scalar_t__ mappedbase; scalar_t__ MIDQ; scalar_t__ MODQ; scalar_t__ DARQ; scalar_t__ DAPQ; int /*<<< orphan*/  lock; scalar_t__ io; int /*<<< orphan*/  memid; } ;

/* Variables and functions */
 int /*<<< orphan*/  DAPQ_BUFF_SIZE ; 
 int /*<<< orphan*/  DAPQ_DATA_BUFF ; 
 scalar_t__ DAPQ_OFFSET ; 
 int /*<<< orphan*/  DARQ_BUFF_SIZE ; 
 int /*<<< orphan*/  DARQ_DATA_BUFF ; 
 scalar_t__ DARQ_OFFSET ; 
 int /*<<< orphan*/  DSPQ_BUFF_SIZE ; 
 int /*<<< orphan*/  DSPQ_DATA_BUFF ; 
 scalar_t__ DSPQ_OFFSET ; 
 int /*<<< orphan*/  HPBLKSEL_0 ; 
 int /*<<< orphan*/  HPBLKSEL_1 ; 
 scalar_t__ HP_BLKS ; 
 scalar_t__ HP_MEMM ; 
 int /*<<< orphan*/  MIDQ_BUFF_SIZE ; 
 int /*<<< orphan*/  MIDQ_DATA_BUFF ; 
 scalar_t__ MIDQ_OFFSET ; 
 int /*<<< orphan*/  MODQ_BUFF_SIZE ; 
 int /*<<< orphan*/  MODQ_DATA_BUFF ; 
 scalar_t__ MODQ_OFFSET ; 
 scalar_t__ SMA_STRUCT_START ; 
 scalar_t__ SMA_dwCurrPlayPitch ; 
 scalar_t__ SMA_dwCurrPlayRate ; 
 scalar_t__ SMA_wCalFreqAtoD ; 
 scalar_t__ SMA_wCurrInputTagBits ; 
 scalar_t__ SMA_wCurrMastVolLeft ; 
 scalar_t__ SMA_wCurrMastVolRight ; 
 scalar_t__ SMA_wCurrPlayChannels ; 
 scalar_t__ SMA_wCurrPlayFormat ; 
 scalar_t__ SMA_wCurrPlaySampleRate ; 
 scalar_t__ SMA_wCurrPlaySampleSize ; 
 int /*<<< orphan*/  memset_io (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,scalar_t__) ; 
 int readw (scalar_t__) ; 
 int /*<<< orphan*/  snd_msnd_init_queue (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 
 int /*<<< orphan*/  writew (int,scalar_t__) ; 

__attribute__((used)) static int snd_msnd_init_sma(struct snd_msnd *chip)
{
	static int initted;
	u16 mastVolLeft, mastVolRight;
	unsigned long flags;

#ifdef MSND_CLASSIC
	outb(chip->memid, chip->io + HP_MEMM);
#endif
	outb(HPBLKSEL_0, chip->io + HP_BLKS);
	/* Motorola 56k shared memory base */
	chip->SMA = chip->mappedbase + SMA_STRUCT_START;

	if (initted) {
		mastVolLeft = readw(chip->SMA + SMA_wCurrMastVolLeft);
		mastVolRight = readw(chip->SMA + SMA_wCurrMastVolRight);
	} else
		mastVolLeft = mastVolRight = 0;
	memset_io(chip->mappedbase, 0, 0x8000);

	/* Critical section: bank 1 access */
	spin_lock_irqsave(&chip->lock, flags);
	outb(HPBLKSEL_1, chip->io + HP_BLKS);
	memset_io(chip->mappedbase, 0, 0x8000);
	outb(HPBLKSEL_0, chip->io + HP_BLKS);
	spin_unlock_irqrestore(&chip->lock, flags);

	/* Digital audio play queue */
	chip->DAPQ = chip->mappedbase + DAPQ_OFFSET;
	snd_msnd_init_queue(chip->DAPQ, DAPQ_DATA_BUFF, DAPQ_BUFF_SIZE);

	/* Digital audio record queue */
	chip->DARQ = chip->mappedbase + DARQ_OFFSET;
	snd_msnd_init_queue(chip->DARQ, DARQ_DATA_BUFF, DARQ_BUFF_SIZE);

	/* MIDI out queue */
	chip->MODQ = chip->mappedbase + MODQ_OFFSET;
	snd_msnd_init_queue(chip->MODQ, MODQ_DATA_BUFF, MODQ_BUFF_SIZE);

	/* MIDI in queue */
	chip->MIDQ = chip->mappedbase + MIDQ_OFFSET;
	snd_msnd_init_queue(chip->MIDQ, MIDQ_DATA_BUFF, MIDQ_BUFF_SIZE);

	/* DSP -> host message queue */
	chip->DSPQ = chip->mappedbase + DSPQ_OFFSET;
	snd_msnd_init_queue(chip->DSPQ, DSPQ_DATA_BUFF, DSPQ_BUFF_SIZE);

	/* Setup some DSP values */
#ifndef MSND_CLASSIC
	writew(1, chip->SMA + SMA_wCurrPlayFormat);
	writew(chip->play_sample_size, chip->SMA + SMA_wCurrPlaySampleSize);
	writew(chip->play_channels, chip->SMA + SMA_wCurrPlayChannels);
	writew(chip->play_sample_rate, chip->SMA + SMA_wCurrPlaySampleRate);
#endif
	writew(chip->play_sample_rate, chip->SMA + SMA_wCalFreqAtoD);
	writew(mastVolLeft, chip->SMA + SMA_wCurrMastVolLeft);
	writew(mastVolRight, chip->SMA + SMA_wCurrMastVolRight);
#ifndef MSND_CLASSIC
	writel(0x00010000, chip->SMA + SMA_dwCurrPlayPitch);
	writel(0x00000001, chip->SMA + SMA_dwCurrPlayRate);
#endif
	writew(0x303, chip->SMA + SMA_wCurrInputTagBits);

	initted = 1;

	return 0;
}