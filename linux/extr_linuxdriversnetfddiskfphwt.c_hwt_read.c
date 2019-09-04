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
typedef  scalar_t__ u_short ;
typedef  int u_long ;
struct TYPE_2__ {scalar_t__ t_start; scalar_t__ t_stop; scalar_t__ timer_activ; } ;
struct s_smc {TYPE_1__ hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADDR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  B2_TI_VAL ; 
 int GET_ISR () ; 
 int IS_TIMINT ; 
 int /*<<< orphan*/  hwt_restart (struct s_smc*) ; 
 int /*<<< orphan*/  hwt_stop (struct s_smc*) ; 
 int inpd (int /*<<< orphan*/ ) ; 

u_long hwt_read(struct s_smc *smc)
{
	u_short	tr ;
	u_long	is ;

	if (smc->hw.timer_activ) {
		hwt_stop(smc) ;
		tr = (u_short)((inpd(ADDR(B2_TI_VAL))/200) & 0xffff) ;

		is = GET_ISR() ;
		/* Check if timer expired (or wraparound). */
		if ((tr > smc->hw.t_start) || (is & IS_TIMINT)) {
			hwt_restart(smc) ;
			smc->hw.t_stop = smc->hw.t_start ;
		}
		else
			smc->hw.t_stop = smc->hw.t_start - tr ;
	}
	return smc->hw.t_stop;
}