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
struct TYPE_2__ {scalar_t__ sas; } ;
struct s_smc {TYPE_1__ s; } ;

/* Variables and functions */
 int NUMPHYS ; 
 scalar_t__ SMT_SAS ; 

__attribute__((used)) static int smt_mib_phys(struct s_smc *smc)
{
#ifdef	CONCENTRATOR
	SK_UNUSED(smc) ;

	return NUMPHYS;
#else
	if (smc->s.sas == SMT_SAS)
		return 1;
	return NUMPHYS;
#endif
}