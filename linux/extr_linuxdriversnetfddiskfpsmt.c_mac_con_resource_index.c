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
struct TYPE_4__ {scalar_t__ sas; } ;
struct TYPE_3__ {int fddiSMTCF_State; } ;
struct s_smc {TYPE_2__ s; TYPE_1__ mib; } ;

/* Variables and functions */
#define  SC10_C_WRAP_B 132 
#define  SC11_C_WRAP_S 131 
#define  SC4_THRU_A 130 
#define  SC5_THRU_B 129 
#define  SC9_C_WRAP_A 128 
 int /*<<< orphan*/  SK_UNUSED (int) ; 
 scalar_t__ SMT_SAS ; 

__attribute__((used)) static int mac_con_resource_index(struct s_smc *smc, int mac)
{
#ifdef	CONCENTRATOR
	SK_UNUSED(smc) ;
	SK_UNUSED(mac) ;
	return entity_to_index(smc, cem_get_downstream(smc, ENTITY_MAC));
#else
	SK_UNUSED(mac) ;
	switch (smc->mib.fddiSMTCF_State) {
	case SC9_C_WRAP_A :
	case SC5_THRU_B :
	case SC11_C_WRAP_S :
		return 1;
	case SC10_C_WRAP_B :
	case SC4_THRU_A :
		return 2;
	}
	return smc->s.sas == SMT_SAS ? 2 : 3;
#endif
}