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
typedef  int /*<<< orphan*/  u32 ;
struct ath5k_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR5K_RXDP ; 
 int /*<<< orphan*/  ath5k_hw_reg_read (struct ath5k_hw*,int /*<<< orphan*/ ) ; 

u32
ath5k_hw_get_rxdp(struct ath5k_hw *ah)
{
	return ath5k_hw_reg_read(ah, AR5K_RXDP);
}