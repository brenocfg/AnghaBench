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
typedef  scalar_t__ u32 ;
struct TYPE_2__ {int /*<<< orphan*/  cwm_ignore_extcca; } ;
struct ath_hw {TYPE_1__ config; } ;
struct ath9k_channel {int dummy; } ;

/* Variables and functions */
 scalar_t__ AR_2040_JOINED_RX_CLEAR ; 
 int /*<<< orphan*/  AR_2040_MODE ; 
 scalar_t__ IS_CHAN_HT40 (struct ath9k_channel*) ; 
 int /*<<< orphan*/  REG_WRITE (struct ath_hw*,int /*<<< orphan*/ ,scalar_t__) ; 

void ath9k_hw_set11nmac2040(struct ath_hw *ah, struct ath9k_channel *chan)
{
	u32 macmode;

	if (IS_CHAN_HT40(chan) && !ah->config.cwm_ignore_extcca)
		macmode = AR_2040_JOINED_RX_CLEAR;
	else
		macmode = 0;

	REG_WRITE(ah, AR_2040_MODE, macmode);
}