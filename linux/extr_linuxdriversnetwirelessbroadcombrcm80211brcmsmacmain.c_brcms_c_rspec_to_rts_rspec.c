#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
typedef  int u16 ;
struct brcms_c_info {TYPE_2__* stf; TYPE_3__* band; TYPE_1__* protection; } ;
struct TYPE_6__ {scalar_t__ gmode; } ;
struct TYPE_5__ {int ss_opmode; } ;
struct TYPE_4__ {scalar_t__ _g; } ;

/* Variables and functions */
 scalar_t__ BRCMS_PHY_11N_CAP (TYPE_3__*) ; 
 int BRCM_RATE_11M ; 
 int PHY_TXC1_BW_40MHZ_DUP ; 
 int RSPEC_BW_MASK ; 
 int RSPEC_BW_SHIFT ; 
 int RSPEC_STF_MASK ; 
 int RSPEC_STF_SHIFT ; 
 int brcms_basic_rate (struct brcms_c_info*,int) ; 
 int /*<<< orphan*/  is_cck_rate (int) ; 
 scalar_t__ is_ofdm_rate (int) ; 
 scalar_t__ rspec_is40mhz (int) ; 

u32
brcms_c_rspec_to_rts_rspec(struct brcms_c_info *wlc, u32 rspec,
			   bool use_rspec, u16 mimo_ctlchbw)
{
	u32 rts_rspec = 0;

	if (use_rspec)
		/* use frame rate as rts rate */
		rts_rspec = rspec;
	else if (wlc->band->gmode && wlc->protection->_g && !is_cck_rate(rspec))
		/* Use 11Mbps as the g protection RTS target rate and fallback.
		 * Use the brcms_basic_rate() lookup to find the best basic rate
		 * under the target in case 11 Mbps is not Basic.
		 * 6 and 9 Mbps are not usually selected by rate selection, but
		 * even if the OFDM rate we are protecting is 6 or 9 Mbps, 11
		 * is more robust.
		 */
		rts_rspec = brcms_basic_rate(wlc, BRCM_RATE_11M);
	else
		/* calculate RTS rate and fallback rate based on the frame rate
		 * RTS must be sent at a basic rate since it is a
		 * control frame, sec 9.6 of 802.11 spec
		 */
		rts_rspec = brcms_basic_rate(wlc, rspec);

	if (BRCMS_PHY_11N_CAP(wlc->band)) {
		/* set rts txbw to correct side band */
		rts_rspec &= ~RSPEC_BW_MASK;

		/*
		 * if rspec/rspec_fallback is 40MHz, then send RTS on both
		 * 20MHz channel (DUP), otherwise send RTS on control channel
		 */
		if (rspec_is40mhz(rspec) && !is_cck_rate(rts_rspec))
			rts_rspec |= (PHY_TXC1_BW_40MHZ_DUP << RSPEC_BW_SHIFT);
		else
			rts_rspec |= (mimo_ctlchbw << RSPEC_BW_SHIFT);

		/* pick siso/cdd as default for ofdm */
		if (is_ofdm_rate(rts_rspec)) {
			rts_rspec &= ~RSPEC_STF_MASK;
			rts_rspec |= (wlc->stf->ss_opmode << RSPEC_STF_SHIFT);
		}
	}
	return rts_rspec;
}