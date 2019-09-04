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
struct TYPE_4__ {int fddiSMTNonMaster_Ct; scalar_t__ fddiSMTMaster_Ct; } ;
struct TYPE_3__ {int sas; } ;
struct s_smc {TYPE_2__ mib; TYPE_1__ s; } ;

/* Variables and functions */
#define  SMT_DAS 129 
#define  SMT_SAS 128 

void smt_fixup_mib(struct s_smc *smc)
{
#ifdef	CONCENTRATOR
	switch (smc->s.sas) {
	case SMT_SAS :
		smc->mib.fddiSMTNonMaster_Ct = 1 ;
		break ;
	case SMT_DAS :
		smc->mib.fddiSMTNonMaster_Ct = 2 ;
		break ;
	case SMT_NAC :
		smc->mib.fddiSMTNonMaster_Ct = 0 ;
		break ;
	}
	smc->mib.fddiSMTMaster_Ct = NUMPHYS - smc->mib.fddiSMTNonMaster_Ct ;
#else
	switch (smc->s.sas) {
	case SMT_SAS :
		smc->mib.fddiSMTNonMaster_Ct = 1 ;
		break ;
	case SMT_DAS :
		smc->mib.fddiSMTNonMaster_Ct = 2 ;
		break ;
	}
	smc->mib.fddiSMTMaster_Ct = 0 ;
#endif
}