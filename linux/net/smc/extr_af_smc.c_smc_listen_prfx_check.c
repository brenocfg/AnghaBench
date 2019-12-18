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
struct socket {int dummy; } ;
struct smc_sock {struct socket* clcsock; } ;
struct smc_clc_msg_proposal_prefix {int dummy; } ;
struct smc_clc_msg_proposal {int dummy; } ;

/* Variables and functions */
 int SMC_CLC_DECL_DIFFPREFIX ; 
 scalar_t__ smc_clc_prfx_match (struct socket*,struct smc_clc_msg_proposal_prefix*) ; 
 struct smc_clc_msg_proposal_prefix* smc_clc_proposal_get_prefix (struct smc_clc_msg_proposal*) ; 

__attribute__((used)) static int smc_listen_prfx_check(struct smc_sock *new_smc,
				 struct smc_clc_msg_proposal *pclc)
{
	struct smc_clc_msg_proposal_prefix *pclc_prfx;
	struct socket *newclcsock = new_smc->clcsock;

	pclc_prfx = smc_clc_proposal_get_prefix(pclc);
	if (smc_clc_prfx_match(newclcsock, pclc_prfx))
		return SMC_CLC_DECL_DIFFPREFIX;

	return 0;
}