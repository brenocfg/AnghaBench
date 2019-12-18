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
struct TYPE_2__ {int channels; int precision; scalar_t__ offset; scalar_t__ onboard; } ;
struct snd_dbri {int /*<<< orphan*/  lock; scalar_t__ regs; TYPE_1__ mm; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHIslave ; 
 int D_C ; 
 int D_ENPIO ; 
 int /*<<< orphan*/  D_MM ; 
 int D_PIO0 ; 
 int D_PIO1 ; 
 int D_PIO2 ; 
 int D_PIO3 ; 
 scalar_t__ REG0 ; 
 scalar_t__ REG2 ; 
 int /*<<< orphan*/  cs4215_setdata (struct snd_dbri*,int) ; 
 int /*<<< orphan*/  dprintk (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  link_time_slot (struct snd_dbri*,int,int,int,int,scalar_t__) ; 
 int /*<<< orphan*/  reset_chi (struct snd_dbri*,int /*<<< orphan*/ ,int) ; 
 int sbus_readl (scalar_t__) ; 
 int /*<<< orphan*/  sbus_writel (int,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void cs4215_open(struct snd_dbri *dbri)
{
	int data_width;
	u32 tmp;
	unsigned long flags;

	dprintk(D_MM, "cs4215_open: %d channels, %d bits\n",
		dbri->mm.channels, dbri->mm.precision);

	/* Temporarily mute outputs, and wait 1/8000 sec (125 us)
	 * to make sure this takes.  This avoids clicking noises.
	 */

	cs4215_setdata(dbri, 1);
	udelay(125);

	/*
	 * Data mode:
	 * Pipe  4: Send timeslots 1-4 (audio data)
	 * Pipe 20: Send timeslots 5-8 (part of ctrl data)
	 * Pipe  6: Receive timeslots 1-4 (audio data)
	 * Pipe 21: Receive timeslots 6-7. We can only receive 20 bits via
	 *          interrupt, and the rest of the data (slot 5 and 8) is
	 *          not relevant for us (only for doublechecking).
	 *
	 * Just like in control mode, the time slots are all offset by eight
	 * bits.  The CS4215, it seems, observes TSIN (the delayed signal)
	 * even if it's the CHI master.  Don't ask me...
	 */
	spin_lock_irqsave(&dbri->lock, flags);
	tmp = sbus_readl(dbri->regs + REG0);
	tmp &= ~(D_C);		/* Disable CHI */
	sbus_writel(tmp, dbri->regs + REG0);

	/* Switch CS4215 to data mode - set PIO3 to 1 */
	sbus_writel(D_ENPIO | D_PIO1 | D_PIO3 |
		    (dbri->mm.onboard ? D_PIO0 : D_PIO2), dbri->regs + REG2);

	reset_chi(dbri, CHIslave, 128);

	/* Note: this next doesn't work for 8-bit stereo, because the two
	 * channels would be on timeslots 1 and 3, with 2 and 4 idle.
	 * (See CS4215 datasheet Fig 15)
	 *
	 * DBRI non-contiguous mode would be required to make this work.
	 */
	data_width = dbri->mm.channels * dbri->mm.precision;

	link_time_slot(dbri, 4, 16, 16, data_width, dbri->mm.offset);
	link_time_slot(dbri, 20, 4, 16, 32, dbri->mm.offset + 32);
	link_time_slot(dbri, 6, 16, 16, data_width, dbri->mm.offset);
	link_time_slot(dbri, 21, 6, 16, 16, dbri->mm.offset + 40);

	/* FIXME: enable CHI after _setdata? */
	tmp = sbus_readl(dbri->regs + REG0);
	tmp |= D_C;		/* Enable CHI */
	sbus_writel(tmp, dbri->regs + REG0);
	spin_unlock_irqrestore(&dbri->lock, flags);

	cs4215_setdata(dbri, 0);
}