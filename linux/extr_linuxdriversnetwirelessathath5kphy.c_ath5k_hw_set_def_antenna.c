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
typedef  int u8 ;
struct ath5k_hw {scalar_t__ ah_version; } ;

/* Variables and functions */
 scalar_t__ AR5K_AR5210 ; 
 int /*<<< orphan*/  AR5K_DEFAULT_ANTENNA ; 
 int /*<<< orphan*/  ath5k_hw_reg_write (struct ath5k_hw*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ath5k_hw_set_def_antenna(struct ath5k_hw *ah, u8 ant)
{
	if (ah->ah_version != AR5K_AR5210)
		ath5k_hw_reg_write(ah, ant & 0x7, AR5K_DEFAULT_ANTENNA);
}