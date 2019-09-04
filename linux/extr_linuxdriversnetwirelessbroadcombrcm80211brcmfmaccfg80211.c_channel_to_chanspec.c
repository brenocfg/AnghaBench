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
typedef  int /*<<< orphan*/  u16 ;
struct ieee80211_channel {int /*<<< orphan*/  center_freq; } ;
struct brcmu_d11inf {int /*<<< orphan*/  (* encchspec ) (struct brcmu_chan*) ;} ;
struct brcmu_chan {int /*<<< orphan*/  chspec; int /*<<< orphan*/  bw; int /*<<< orphan*/  chnum; } ;

/* Variables and functions */
 int /*<<< orphan*/  BRCMU_CHAN_BW_20 ; 
 int /*<<< orphan*/  ieee80211_frequency_to_channel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct brcmu_chan*) ; 

u16 channel_to_chanspec(struct brcmu_d11inf *d11inf,
			struct ieee80211_channel *ch)
{
	struct brcmu_chan ch_inf;

	ch_inf.chnum = ieee80211_frequency_to_channel(ch->center_freq);
	ch_inf.bw = BRCMU_CHAN_BW_20;
	d11inf->encchspec(&ch_inf);

	return ch_inf.chspec;
}