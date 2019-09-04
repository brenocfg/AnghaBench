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
typedef  int /*<<< orphan*/  u16 ;
typedef  enum brcmu_chan_sb { ____Placeholder_brcmu_chan_sb } brcmu_chan_sb ;

/* Variables and functions */
#define  BRCMU_CHAN_SB_L 130 
#define  BRCMU_CHAN_SB_NONE 129 
#define  BRCMU_CHAN_SB_U 128 
 int /*<<< orphan*/  BRCMU_CHSPEC_D11N_SB_L ; 
 int /*<<< orphan*/  BRCMU_CHSPEC_D11N_SB_N ; 
 int /*<<< orphan*/  BRCMU_CHSPEC_D11N_SB_U ; 
 int /*<<< orphan*/  WARN_ON (int) ; 

__attribute__((used)) static u16 d11n_sb(enum brcmu_chan_sb sb)
{
	switch (sb) {
	case BRCMU_CHAN_SB_NONE:
		return BRCMU_CHSPEC_D11N_SB_N;
	case BRCMU_CHAN_SB_L:
		return BRCMU_CHSPEC_D11N_SB_L;
	case BRCMU_CHAN_SB_U:
		return BRCMU_CHSPEC_D11N_SB_U;
	default:
		WARN_ON(1);
	}
	return 0;
}