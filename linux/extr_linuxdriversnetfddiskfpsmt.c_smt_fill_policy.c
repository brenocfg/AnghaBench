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
typedef  int u_short ;
typedef  int u_char ;
struct smt_p_policy {int pl_connect; int /*<<< orphan*/  pl_config; } ;
struct TYPE_2__ {int fddiSMTConnectionPolicy; int /*<<< orphan*/  fddiSMTConfigPolicy; } ;
struct s_smc {TYPE_1__ mib; } ;

/* Variables and functions */
 int /*<<< orphan*/  SMTSETPARA (struct smt_p_policy*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SMT_P_POLICY ; 

__attribute__((used)) static void smt_fill_policy(struct s_smc *smc, struct smt_p_policy *policy)
{
	int	i ;
	const u_char *map ;
	u_short	in ;
	u_short	out ;

	/*
	 * MIB para 101b (fddiSMTConnectionPolicy) coding
	 * is different from 0005 coding
	 */
	static const u_char ansi_weirdness[16] = {
		0,7,5,3,8,1,6,4,9,10,2,11,12,13,14,15
	} ;
	SMTSETPARA(policy,SMT_P_POLICY) ;

	out = 0 ;
	in = smc->mib.fddiSMTConnectionPolicy ;
	for (i = 0, map = ansi_weirdness ; i < 16 ; i++) {
		if (in & 1)
			out |= (1<<*map) ;
		in >>= 1 ;
		map++ ;
	}
	policy->pl_config = smc->mib.fddiSMTConfigPolicy ;
	policy->pl_connect = out ;
}