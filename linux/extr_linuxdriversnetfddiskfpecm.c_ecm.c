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
struct TYPE_2__ {int fddiSMTECMState; } ;
struct s_smc {TYPE_1__ mib; } ;

/* Variables and functions */
 int AFLAG ; 
 int /*<<< orphan*/  DB_ECM (char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ecm_events ; 
 int /*<<< orphan*/  ecm_fsm (struct s_smc*,int) ; 
 int /*<<< orphan*/  ecm_state_change (struct s_smc*,int) ; 
 int /*<<< orphan*/ * ecm_states ; 

void ecm(struct s_smc *smc, int event)
{
	int	state ;

	do {
		DB_ECM("ECM : state %s%s event %s",
		       smc->mib.fddiSMTECMState & AFLAG ? "ACTIONS " : "",
		       ecm_states[smc->mib.fddiSMTECMState & ~AFLAG],
		       ecm_events[event]);
		state = smc->mib.fddiSMTECMState ;
		ecm_fsm(smc,event) ;
		event = 0 ;
	} while (state != smc->mib.fddiSMTECMState) ;
	ecm_state_change(smc,(int)smc->mib.fddiSMTECMState) ;
}