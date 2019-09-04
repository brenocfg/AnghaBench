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
typedef  int /*<<< orphan*/  u32 ;
struct ath_regulatory {int dummy; } ;
struct ath9k_channel {TYPE_1__* chan; } ;
struct TYPE_2__ {int /*<<< orphan*/  band; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTL_11A ; 
 int /*<<< orphan*/  CTL_11G ; 
 scalar_t__ IS_CHAN_2GHZ (struct ath9k_channel*) ; 
 int /*<<< orphan*/  ath_regd_get_band_ctl (struct ath_regulatory*,int /*<<< orphan*/ ) ; 

u32 ath9k_regd_get_ctl(struct ath_regulatory *reg, struct ath9k_channel *chan)
{
	u32 ctl = ath_regd_get_band_ctl(reg, chan->chan->band);

	if (IS_CHAN_2GHZ(chan))
		ctl |= CTL_11G;
	else
		ctl |= CTL_11A;

	return ctl;
}