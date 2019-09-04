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
struct ath5k_hw {scalar_t__ ah_version; } ;

/* Variables and functions */
 scalar_t__ AR5K_AR5210 ; 
 int /*<<< orphan*/  AR5K_REG_ENABLE_BITS (struct ath5k_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  AR5K_STA_ID1 ; 
 int AR5K_STA_ID1_DEFAULT_ANTENNA ; 
 int AR5K_STA_ID1_NO_PSPOLL ; 
 int EIO ; 

int ath5k_hw_disable_pspoll(struct ath5k_hw *ah)
{
	if (ah->ah_version == AR5K_AR5210) {
		AR5K_REG_ENABLE_BITS(ah, AR5K_STA_ID1,
			AR5K_STA_ID1_NO_PSPOLL | AR5K_STA_ID1_DEFAULT_ANTENNA);
		return 0;
	}

	return -EIO;
}