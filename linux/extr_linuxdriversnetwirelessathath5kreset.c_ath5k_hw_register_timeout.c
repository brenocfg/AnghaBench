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
typedef  int u32 ;
struct ath5k_hw {int dummy; } ;

/* Variables and functions */
 int AR5K_TUNE_REGISTER_TIMEOUT ; 
 int EAGAIN ; 
 int ath5k_hw_reg_read (struct ath5k_hw*,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

int
ath5k_hw_register_timeout(struct ath5k_hw *ah, u32 reg, u32 flag, u32 val,
			      bool is_set)
{
	int i;
	u32 data;

	for (i = AR5K_TUNE_REGISTER_TIMEOUT; i > 0; i--) {
		data = ath5k_hw_reg_read(ah, reg);
		if (is_set && (data & flag))
			break;
		else if ((data & flag) == val)
			break;
		udelay(15);
	}

	return (i <= 0) ? -EAGAIN : 0;
}