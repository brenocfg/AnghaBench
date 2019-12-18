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
struct minstrel_rate {void* ack_time; void* perfect_tx_time; } ;
struct ieee80211_rate {int flags; int /*<<< orphan*/  bitrate; } ;
struct cfg80211_chan_def {int dummy; } ;
typedef  enum nl80211_band { ____Placeholder_nl80211_band } nl80211_band ;

/* Variables and functions */
 int /*<<< orphan*/  DIV_ROUND_UP (int /*<<< orphan*/ ,int) ; 
 int IEEE80211_RATE_ERP_G ; 
 int ieee80211_chandef_get_shift (struct cfg80211_chan_def*) ; 
 void* ieee80211_frame_duration (int,int,int /*<<< orphan*/ ,int,int,int) ; 

__attribute__((used)) static void
calc_rate_durations(enum nl80211_band band,
		    struct minstrel_rate *d,
		    struct ieee80211_rate *rate,
		    struct cfg80211_chan_def *chandef)
{
	int erp = !!(rate->flags & IEEE80211_RATE_ERP_G);
	int shift = ieee80211_chandef_get_shift(chandef);

	d->perfect_tx_time = ieee80211_frame_duration(band, 1200,
			DIV_ROUND_UP(rate->bitrate, 1 << shift), erp, 1,
			shift);
	d->ack_time = ieee80211_frame_duration(band, 10,
			DIV_ROUND_UP(rate->bitrate, 1 << shift), erp, 1,
			shift);
}