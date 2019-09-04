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
struct ath5k_hw {int** rate_idx; TYPE_1__* curchan; } ;
struct TYPE_2__ {size_t band; } ;

/* Variables and functions */
 int AR5K_MAX_RATES ; 
 scalar_t__ WARN (int,char*,int) ; 

__attribute__((used)) static inline int
ath5k_hw_to_driver_rix(struct ath5k_hw *ah, int hw_rix)
{
	int rix;

	/* return base rate on errors */
	if (WARN(hw_rix < 0 || hw_rix >= AR5K_MAX_RATES,
			"hw_rix out of bounds: %x\n", hw_rix))
		return 0;

	rix = ah->rate_idx[ah->curchan->band][hw_rix];
	if (WARN(rix < 0, "invalid hw_rix: %x\n", hw_rix))
		rix = 0;

	return rix;
}