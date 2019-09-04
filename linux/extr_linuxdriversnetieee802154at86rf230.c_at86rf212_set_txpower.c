#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u32 ;
struct at86rf230_local {TYPE_3__* hw; } ;
typedef  scalar_t__ s32 ;
struct TYPE_6__ {TYPE_2__* phy; } ;
struct TYPE_4__ {size_t tx_powers_size; scalar_t__* tx_powers; } ;
struct TYPE_5__ {TYPE_1__ supported; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  SR_TX_PWR_212 ; 
 int at86rf230_write_subreg (struct at86rf230_local*,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static int
at86rf212_set_txpower(struct at86rf230_local *lp, s32 mbm)
{
	u32 i;

	for (i = 0; i < lp->hw->phy->supported.tx_powers_size; i++) {
		if (lp->hw->phy->supported.tx_powers[i] == mbm)
			return at86rf230_write_subreg(lp, SR_TX_PWR_212, i);
	}

	return -EINVAL;
}