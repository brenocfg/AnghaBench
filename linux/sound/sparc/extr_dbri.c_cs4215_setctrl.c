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
struct TYPE_2__ {int status; int /*<<< orphan*/ * ctrl; scalar_t__ offset; scalar_t__ onboard; } ;
struct snd_dbri {TYPE_1__ mm; int /*<<< orphan*/  lock; scalar_t__ regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHImaster ; 
 int /*<<< orphan*/  CS4215_CLB ; 
 int D_C ; 
 int D_ENPIO ; 
 int /*<<< orphan*/  D_MM ; 
 int D_PIO0 ; 
 int D_PIO1 ; 
 int D_PIO2 ; 
 scalar_t__ REG0 ; 
 scalar_t__ REG2 ; 
 int /*<<< orphan*/  cs4215_setdata (struct snd_dbri*,int) ; 
 int /*<<< orphan*/  dprintk (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  link_time_slot (struct snd_dbri*,int,int,int,int,scalar_t__) ; 
 int /*<<< orphan*/  msleep_interruptible (int) ; 
 int /*<<< orphan*/  recv_fixed (struct snd_dbri*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reset_chi (struct snd_dbri*,int /*<<< orphan*/ ,int) ; 
 int sbus_readl (scalar_t__) ; 
 int /*<<< orphan*/  sbus_writel (int,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  xmit_fixed (struct snd_dbri*,int,int) ; 

__attribute__((used)) static int cs4215_setctrl(struct snd_dbri *dbri)
{
	int i, val;
	u32 tmp;
	unsigned long flags;

	/* FIXME - let the CPU do something useful during these delays */

	/* Temporarily mute outputs, and wait 1/8000 sec (125 us)
	 * to make sure this takes.  This avoids clicking noises.
	 */
	cs4215_setdata(dbri, 1);
	udelay(125);

	/*
	 * Enable Control mode: Set DBRI's PIO3 (4215's D/~C) to 0, then wait
	 * 12 cycles <= 12/(5512.5*64) sec = 34.01 usec
	 */
	val = D_ENPIO | D_PIO1 | (dbri->mm.onboard ? D_PIO0 : D_PIO2);
	sbus_writel(val, dbri->regs + REG2);
	dprintk(D_MM, "cs4215_setctrl: reg2=0x%x\n", val);
	udelay(34);

	/* In Control mode, the CS4215 is a slave device, so the DBRI must
	 * operate as CHI master, supplying clocking and frame synchronization.
	 *
	 * In Data mode, however, the CS4215 must be CHI master to insure
	 * that its data stream is synchronous with its codec.
	 *
	 * The upshot of all this?  We start by putting the DBRI into master
	 * mode, program the CS4215 in Control mode, then switch the CS4215
	 * into Data mode and put the DBRI into slave mode.  Various timing
	 * requirements must be observed along the way.
	 *
	 * Oh, and one more thing, on a SPARCStation 20 (and maybe
	 * others?), the addressing of the CS4215's time slots is
	 * offset by eight bits, so we add eight to all the "cycle"
	 * values in the Define Time Slot (DTS) commands.  This is
	 * done in hardware by a TI 248 that delays the DBRI->4215
	 * frame sync signal by eight clock cycles.  Anybody know why?
	 */
	spin_lock_irqsave(&dbri->lock, flags);
	tmp = sbus_readl(dbri->regs + REG0);
	tmp &= ~D_C;		/* Disable CHI */
	sbus_writel(tmp, dbri->regs + REG0);

	reset_chi(dbri, CHImaster, 128);

	/*
	 * Control mode:
	 * Pipe 17: Send timeslots 1-4 (slots 5-8 are read only)
	 * Pipe 18: Receive timeslot 1 (clb).
	 * Pipe 19: Receive timeslot 7 (version).
	 */

	link_time_slot(dbri, 17, 16, 16, 32, dbri->mm.offset);
	link_time_slot(dbri, 18, 16, 16, 8, dbri->mm.offset);
	link_time_slot(dbri, 19, 18, 16, 8, dbri->mm.offset + 48);
	spin_unlock_irqrestore(&dbri->lock, flags);

	/* Wait for the chip to echo back CLB (Control Latch Bit) as zero */
	dbri->mm.ctrl[0] &= ~CS4215_CLB;
	xmit_fixed(dbri, 17, *(int *)dbri->mm.ctrl);

	spin_lock_irqsave(&dbri->lock, flags);
	tmp = sbus_readl(dbri->regs + REG0);
	tmp |= D_C;		/* Enable CHI */
	sbus_writel(tmp, dbri->regs + REG0);
	spin_unlock_irqrestore(&dbri->lock, flags);

	for (i = 10; ((dbri->mm.status & 0xe4) != 0x20); --i)
		msleep_interruptible(1);

	if (i == 0) {
		dprintk(D_MM, "CS4215 didn't respond to CLB (0x%02x)\n",
			dbri->mm.status);
		return -1;
	}

	/* Disable changes to our copy of the version number, as we are about
	 * to leave control mode.
	 */
	recv_fixed(dbri, 19, NULL);

	/* Terminate CS4215 control mode - data sheet says
	 * "Set CLB=1 and send two more frames of valid control info"
	 */
	dbri->mm.ctrl[0] |= CS4215_CLB;
	xmit_fixed(dbri, 17, *(int *)dbri->mm.ctrl);

	/* Two frames of control info @ 8kHz frame rate = 250 us delay */
	udelay(250);

	cs4215_setdata(dbri, 0);

	return 0;
}