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
struct smc_link {int dummy; } ;
struct smc_buf_desc {int wr_reg; int regerr; int /*<<< orphan*/ * mr_rx; } ;

/* Variables and functions */
 int EFAULT ; 
 size_t SMC_SINGLE_LINK ; 
 scalar_t__ smc_llc_do_confirm_rkey (struct smc_link*,struct smc_buf_desc*) ; 
 scalar_t__ smc_wr_reg_send (struct smc_link*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int smc_reg_rmb(struct smc_link *link, struct smc_buf_desc *rmb_desc,
		       bool conf_rkey)
{
	if (!rmb_desc->wr_reg) {
		/* register memory region for new rmb */
		if (smc_wr_reg_send(link, rmb_desc->mr_rx[SMC_SINGLE_LINK])) {
			rmb_desc->regerr = 1;
			return -EFAULT;
		}
		rmb_desc->wr_reg = 1;
	}
	if (!conf_rkey)
		return 0;
	/* exchange confirm_rkey msg with peer */
	if (smc_llc_do_confirm_rkey(link, rmb_desc)) {
		rmb_desc->regerr = 1;
		return -EFAULT;
	}
	return 0;
}