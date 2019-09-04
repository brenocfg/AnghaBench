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
struct TYPE_2__ {int fddiSMTCF_State; } ;
struct s_smc {TYPE_1__ mib; } ;

/* Variables and functions */
 int PA ; 
#define  SC10_C_WRAP_B 132 
#define  SC11_C_WRAP_S 131 
#define  SC4_THRU_A 130 
#define  SC5_THRU_B 129 
#define  SC9_C_WRAP_A 128 

__attribute__((used)) static int phy_con_resource_index(struct s_smc *smc, int phy)
{
#ifdef	CONCENTRATOR
	return entity_to_index(smc, cem_get_downstream(smc, ENTITY_PHY(phy))) ;
#else
	switch (smc->mib.fddiSMTCF_State) {
	case SC9_C_WRAP_A :
		return phy == PA ? 3 : 2;
	case SC10_C_WRAP_B :
		return phy == PA ? 1 : 3;
	case SC4_THRU_A :
		return phy == PA ? 3 : 1;
	case SC5_THRU_B :
		return phy == PA ? 2 : 3;
	case SC11_C_WRAP_S :
		return 2;
	}
	return phy;
#endif
}