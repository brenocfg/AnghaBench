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
 int /*<<< orphan*/  S626_CLKENAB_ALWAYS ; 
 int /*<<< orphan*/  S626_CLKENAB_INDEX ; 
 int /*<<< orphan*/  S626_CLKMULT_1X ; 
 int /*<<< orphan*/  S626_CLKPOL_POS ; 
 int /*<<< orphan*/  S626_ENCMODE_COUNTER ; 
 int S626_ENCODER_CHANNELS ; 
 int /*<<< orphan*/  S626_INDXSRC_SOFT ; 
 int /*<<< orphan*/  S626_LOADSRC_INDX ; 
 int S626_SET_STD_CLKENAB (int /*<<< orphan*/ ) ; 
 int S626_SET_STD_CLKMULT (int /*<<< orphan*/ ) ; 
 int S626_SET_STD_CLKPOL (int /*<<< orphan*/ ) ; 
 int S626_SET_STD_ENCMODE (int /*<<< orphan*/ ) ; 
 int S626_SET_STD_INDXSRC (int /*<<< orphan*/ ) ; 
 int S626_SET_STD_LOADSRC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s626_reset_cap_flags (struct comedi_device*,int) ; 
 int /*<<< orphan*/  s626_set_enable (struct comedi_device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s626_set_int_src (struct comedi_device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s626_set_mode (struct comedi_device*,int,int,int) ; 

__attribute__((used)) static void s626_counters_init(struct comedi_device *dev)
{
	int chan;
	u16 setup =
		/* Preload upon index. */
		S626_SET_STD_LOADSRC(S626_LOADSRC_INDX) |
		/* Disable hardware index. */
		S626_SET_STD_INDXSRC(S626_INDXSRC_SOFT) |
		/* Operating mode is counter. */
		S626_SET_STD_ENCMODE(S626_ENCMODE_COUNTER) |
		/* Active high clock. */
		S626_SET_STD_CLKPOL(S626_CLKPOL_POS) |
		/* Clock multiplier is 1x. */
		S626_SET_STD_CLKMULT(S626_CLKMULT_1X) |
		/* Enabled by index */
		S626_SET_STD_CLKENAB(S626_CLKENAB_INDEX);

	/*
	 * Disable all counter interrupts and clear any captured counter events.
	 */
	for (chan = 0; chan < S626_ENCODER_CHANNELS; chan++) {
		s626_set_mode(dev, chan, setup, true);
		s626_set_int_src(dev, chan, 0);
		s626_reset_cap_flags(dev, chan);
		s626_set_enable(dev, chan, S626_CLKENAB_ALWAYS);
	}
}