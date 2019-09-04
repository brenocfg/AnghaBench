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
struct s_smc {struct s_phy* y; } ;
struct s_phy {struct fddi_mib_p* mib; } ;
struct TYPE_2__ {int R_val; } ;
struct fddi_mib_p {int fddiPORTMy_Type; int fddiPORTConnectState; int fddiPORTNeighborType; int fddiPORTPCMState; TYPE_1__ fddiPORTMacIndicated; } ;

/* Variables and functions */
#define  PC8_ACTIVE 128 

void pcm_status_state(struct s_smc *smc, int np, int *type, int *state,
		      int *remote, int *mac)
{
	struct s_phy	*phy = &smc->y[np] ;
	struct fddi_mib_p	*mib ;

	mib = phy->mib ;

	/* remote PHY type and MAC - set only if active */
	*mac = 0 ;
	*type = mib->fddiPORTMy_Type ;		/* our PHY type */
	*state = mib->fddiPORTConnectState ;
	*remote = mib->fddiPORTNeighborType ;

	switch(mib->fddiPORTPCMState) {
	case PC8_ACTIVE :
		*mac = mib->fddiPORTMacIndicated.R_val ;
		break ;
	}
}