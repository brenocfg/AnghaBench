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
struct TYPE_2__ {scalar_t__ n_a_send; } ;
struct s_smc {TYPE_1__ hw; } ;

/* Variables and functions */

void llc_recover_tx(struct s_smc *smc)
{
#ifdef	LOAD_GEN
	extern	int load_gen_flag ;

	load_gen_flag = 0 ;
#endif
#ifndef	SYNC
	smc->hw.n_a_send= 0 ;
#else
	SK_UNUSED(smc) ;
#endif
}