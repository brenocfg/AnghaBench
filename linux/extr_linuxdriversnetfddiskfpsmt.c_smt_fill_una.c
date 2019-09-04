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
struct smt_p_una {int /*<<< orphan*/  una_node; scalar_t__ una_pad; } ;
struct TYPE_4__ {TYPE_1__* m; } ;
struct s_smc {TYPE_2__ mib; } ;
struct TYPE_3__ {int /*<<< orphan*/  fddiMACUpstreamNbr; } ;

/* Variables and functions */
 size_t MAC0 ; 
 int /*<<< orphan*/  SMTSETPARA (struct smt_p_una*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SMT_P_UNA ; 

__attribute__((used)) static void smt_fill_una(struct s_smc *smc, struct smt_p_una *una)
{
	SMTSETPARA(una,SMT_P_UNA) ;
	una->una_pad = 0 ;
	una->una_node = smc->mib.m[MAC0].fddiMACUpstreamNbr ;
}