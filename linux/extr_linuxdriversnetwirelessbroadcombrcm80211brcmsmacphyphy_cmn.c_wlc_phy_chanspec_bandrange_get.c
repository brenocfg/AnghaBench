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
typedef  int /*<<< orphan*/  uint ;
typedef  int /*<<< orphan*/  u16 ;
struct brcms_phy {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHSPEC_CHANNEL (int /*<<< orphan*/ ) ; 
 scalar_t__ ISLCNPHY (struct brcms_phy*) ; 
 scalar_t__ ISNPHY (struct brcms_phy*) ; 
 int /*<<< orphan*/  wlc_phy_channel2freq (int /*<<< orphan*/ ) ; 
 int wlc_phy_chanspec_freq2bandrange_lpssn (int /*<<< orphan*/ ) ; 
 int wlc_phy_get_chan_freq_range_nphy (struct brcms_phy*,int /*<<< orphan*/ ) ; 

int wlc_phy_chanspec_bandrange_get(struct brcms_phy *pi, u16 chanspec)
{
	int range = -1;
	uint channel = CHSPEC_CHANNEL(chanspec);
	uint freq = wlc_phy_channel2freq(channel);

	if (ISNPHY(pi))
		range = wlc_phy_get_chan_freq_range_nphy(pi, channel);
	else if (ISLCNPHY(pi))
		range = wlc_phy_chanspec_freq2bandrange_lpssn(freq);

	return range;
}