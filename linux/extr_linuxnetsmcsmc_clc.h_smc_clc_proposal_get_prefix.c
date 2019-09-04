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
typedef  int /*<<< orphan*/  u8 ;
struct smc_clc_msg_proposal_prefix {int dummy; } ;
struct smc_clc_msg_proposal {int /*<<< orphan*/  iparea_offset; } ;

/* Variables and functions */
 int ntohs (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline struct smc_clc_msg_proposal_prefix *
smc_clc_proposal_get_prefix(struct smc_clc_msg_proposal *pclc)
{
	return (struct smc_clc_msg_proposal_prefix *)
	       ((u8 *)pclc + sizeof(*pclc) + ntohs(pclc->iparea_offset));
}