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
struct TYPE_2__ {int hw_caps; } ;
struct ath_hw {TYPE_1__ caps; struct ath9k_channel* curchan; } ;
struct ath_common {unsigned int clockrate; } ;
struct ath9k_channel {int dummy; } ;

/* Variables and functions */
 scalar_t__ AR_SREV_9287 (struct ath_hw*) ; 
 scalar_t__ AR_SREV_9287_13_OR_LATER (struct ath_hw*) ; 
 unsigned int ATH9K_CLOCK_FAST_RATE_5GHZ_OFDM ; 
 unsigned int ATH9K_CLOCK_RATE_2GHZ_OFDM ; 
 unsigned int ATH9K_CLOCK_RATE_5GHZ_OFDM ; 
 unsigned int ATH9K_CLOCK_RATE_CCK ; 
 int ATH9K_HW_CAP_FASTCLOCK ; 
 scalar_t__ IS_CHAN_2GHZ (struct ath9k_channel*) ; 
 scalar_t__ IS_CHAN_HALF_RATE (struct ath9k_channel*) ; 
 scalar_t__ IS_CHAN_HT40 (struct ath9k_channel*) ; 
 scalar_t__ IS_CHAN_QUARTER_RATE (struct ath9k_channel*) ; 
 struct ath_common* ath9k_hw_common (struct ath_hw*) ; 

__attribute__((used)) static void ath9k_hw_set_clockrate(struct ath_hw *ah)
{
	struct ath_common *common = ath9k_hw_common(ah);
	struct ath9k_channel *chan = ah->curchan;
	unsigned int clockrate;

	/* AR9287 v1.3+ uses async FIFO and runs the MAC at 117 MHz */
	if (AR_SREV_9287(ah) && AR_SREV_9287_13_OR_LATER(ah))
		clockrate = 117;
	else if (!chan) /* should really check for CCK instead */
		clockrate = ATH9K_CLOCK_RATE_CCK;
	else if (IS_CHAN_2GHZ(chan))
		clockrate = ATH9K_CLOCK_RATE_2GHZ_OFDM;
	else if (ah->caps.hw_caps & ATH9K_HW_CAP_FASTCLOCK)
		clockrate = ATH9K_CLOCK_FAST_RATE_5GHZ_OFDM;
	else
		clockrate = ATH9K_CLOCK_RATE_5GHZ_OFDM;

	if (chan) {
		if (IS_CHAN_HT40(chan))
			clockrate *= 2;
		if (IS_CHAN_HALF_RATE(chan))
			clockrate /= 2;
		if (IS_CHAN_QUARTER_RATE(chan))
			clockrate /= 4;
	}

	common->clockrate = clockrate;
}