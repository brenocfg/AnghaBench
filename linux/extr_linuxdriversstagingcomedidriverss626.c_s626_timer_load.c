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
struct comedi_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  S626_CLKENAB_INDEX ; 
 int /*<<< orphan*/  S626_CLKMULT_1X ; 
 int /*<<< orphan*/  S626_CNTDIR_DOWN ; 
 int /*<<< orphan*/  S626_ENCMODE_TIMER ; 
 int /*<<< orphan*/  S626_INDXSRC_SOFT ; 
 int /*<<< orphan*/  S626_INTSRC_OVER ; 
 int S626_LATCHSRC_A_INDXA ; 
 int /*<<< orphan*/  S626_LOADSRC_INDX ; 
 int S626_SET_STD_CLKENAB (int /*<<< orphan*/ ) ; 
 int S626_SET_STD_CLKMULT (int /*<<< orphan*/ ) ; 
 int S626_SET_STD_CLKPOL (int /*<<< orphan*/ ) ; 
 int S626_SET_STD_ENCMODE (int /*<<< orphan*/ ) ; 
 int S626_SET_STD_INDXSRC (int /*<<< orphan*/ ) ; 
 int S626_SET_STD_LOADSRC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s626_preload (struct comedi_device*,unsigned int,int) ; 
 int /*<<< orphan*/  s626_pulse_index (struct comedi_device*,unsigned int) ; 
 int /*<<< orphan*/  s626_set_int_src (struct comedi_device*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s626_set_latch_source (struct comedi_device*,unsigned int,int) ; 
 int /*<<< orphan*/  s626_set_load_trig (struct comedi_device*,unsigned int,int) ; 
 int /*<<< orphan*/  s626_set_mode (struct comedi_device*,unsigned int,int,int) ; 

__attribute__((used)) static void s626_timer_load(struct comedi_device *dev,
			    unsigned int chan, int tick)
{
	u16 setup =
		/* Preload upon index. */
		S626_SET_STD_LOADSRC(S626_LOADSRC_INDX) |
		/* Disable hardware index. */
		S626_SET_STD_INDXSRC(S626_INDXSRC_SOFT) |
		/* Operating mode is Timer. */
		S626_SET_STD_ENCMODE(S626_ENCMODE_TIMER) |
		/* Count direction is Down. */
		S626_SET_STD_CLKPOL(S626_CNTDIR_DOWN) |
		/* Clock multiplier is 1x. */
		S626_SET_STD_CLKMULT(S626_CLKMULT_1X) |
		/* Enabled by index */
		S626_SET_STD_CLKENAB(S626_CLKENAB_INDEX);
	u16 value_latchsrc = S626_LATCHSRC_A_INDXA;
	/* uint16_t enab = S626_CLKENAB_ALWAYS; */

	s626_set_mode(dev, chan, setup, false);

	/* Set the preload register */
	s626_preload(dev, chan, tick);

	/*
	 * Software index pulse forces the preload register to load
	 * into the counter
	 */
	s626_set_load_trig(dev, chan, 0);
	s626_pulse_index(dev, chan);

	/* set reload on counter overflow */
	s626_set_load_trig(dev, chan, 1);

	/* set interrupt on overflow */
	s626_set_int_src(dev, chan, S626_INTSRC_OVER);

	s626_set_latch_source(dev, chan, value_latchsrc);
	/* s626_set_enable(dev, chan, (uint16_t)(enab != 0)); */
}