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
typedef  int u32 ;
struct davinci_mcasp {int dummy; } ;

/* Variables and functions */
 int AFSRE ; 
 int /*<<< orphan*/  DAVINCI_MCASP_ACLKXCTL_REG ; 
 int /*<<< orphan*/  DAVINCI_MCASP_RXFMCTL_REG ; 
 int TX_ASYNC ; 
 int mcasp_get_reg (struct davinci_mcasp*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool mcasp_is_synchronous(struct davinci_mcasp *mcasp)
{
	u32 rxfmctl = mcasp_get_reg(mcasp, DAVINCI_MCASP_RXFMCTL_REG);
	u32 aclkxctl = mcasp_get_reg(mcasp, DAVINCI_MCASP_ACLKXCTL_REG);

	return !(aclkxctl & TX_ASYNC) && rxfmctl & AFSRE;
}