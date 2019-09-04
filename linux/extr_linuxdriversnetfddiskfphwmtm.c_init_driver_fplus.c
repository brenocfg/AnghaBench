#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int mdr2init; int mdr3init; } ;
struct TYPE_4__ {TYPE_1__ fp; } ;
struct s_smc {TYPE_2__ hw; } ;

/* Variables and functions */
 int FM_BMMODE ; 
 int FM_ENHSRQ ; 
 int FM_ENNPRQ ; 
 int FM_LSB ; 
 int FM_MENRQAUNLCK ; 
 int FM_MENRS ; 

void init_driver_fplus(struct s_smc *smc)
{
	smc->hw.fp.mdr2init = FM_LSB | FM_BMMODE | FM_ENNPRQ | FM_ENHSRQ | 3 ;

#ifdef	PCI
	smc->hw.fp.mdr2init |= FM_CHKPAR | FM_PARITY ;
#endif
	smc->hw.fp.mdr3init = FM_MENRQAUNLCK | FM_MENRS ;

#ifdef	USE_CAN_ADDR
	/* enable address bit swapping */
	smc->hw.fp.frselreg_init = FM_ENXMTADSWAP | FM_ENRCVADSWAP ;
#endif
}