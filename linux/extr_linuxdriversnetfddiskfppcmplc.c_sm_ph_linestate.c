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
struct s_smc {int dummy; } ;

/* Variables and functions */
#define  PC_HLS 132 
#define  PC_ILS 131 
#define  PC_LS_PDR 130 
#define  PC_MLS 129 
#define  PC_QLS 128 
 int /*<<< orphan*/  PLC (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PL_CNTRL_B ; 
 int PL_MAINT ; 
 int PL_MAINT_LS ; 
 int PL_M_HALT ; 
 int PL_M_IDLE ; 
 int PL_M_MASTR ; 
 int PL_M_QUI0 ; 
 int PL_M_TPDR ; 
 int PL_PCM_STOP ; 
 int /*<<< orphan*/  SK_UNUSED (struct s_smc*) ; 
 int inpw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outpw (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void sm_ph_linestate(struct s_smc *smc, int phy, int ls)
{
	int	cntrl ;

	SK_UNUSED(smc) ;

	cntrl = (inpw(PLC(phy,PL_CNTRL_B)) & ~PL_MAINT_LS) |
						PL_PCM_STOP | PL_MAINT ;
	switch(ls) {
	case PC_QLS: 		/* Force Quiet */
		cntrl |= PL_M_QUI0 ;
		break ;
	case PC_MLS: 		/* Force Master */
		cntrl |= PL_M_MASTR ;
		break ;
	case PC_HLS: 		/* Force Halt */
		cntrl |= PL_M_HALT ;
		break ;
	default :
	case PC_ILS: 		/* Force Idle */
		cntrl |= PL_M_IDLE ;
		break ;
	case PC_LS_PDR: 	/* Enable repeat filter */
		cntrl |= PL_M_TPDR ;
		break ;
	}
	outpw(PLC(phy,PL_CNTRL_B),cntrl) ;
}