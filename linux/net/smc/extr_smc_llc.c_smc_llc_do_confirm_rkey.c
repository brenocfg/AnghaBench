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
struct smc_link {scalar_t__ llc_confirm_rkey_rc; int /*<<< orphan*/  llc_confirm_rkey; } ;
struct smc_buf_desc {int dummy; } ;

/* Variables and functions */
 int EFAULT ; 
 int /*<<< orphan*/  SMC_LLC_WAIT_TIME ; 
 int /*<<< orphan*/  reinit_completion (int /*<<< orphan*/ *) ; 
 int smc_llc_send_confirm_rkey (struct smc_link*,struct smc_buf_desc*) ; 
 int wait_for_completion_interruptible_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int smc_llc_do_confirm_rkey(struct smc_link *link,
			    struct smc_buf_desc *rmb_desc)
{
	int rc;

	/* protected by mutex smc_create_lgr_pending */
	reinit_completion(&link->llc_confirm_rkey);
	rc = smc_llc_send_confirm_rkey(link, rmb_desc);
	if (rc)
		return rc;
	/* receive CONFIRM RKEY response from server over RoCE fabric */
	rc = wait_for_completion_interruptible_timeout(&link->llc_confirm_rkey,
						       SMC_LLC_WAIT_TIME);
	if (rc <= 0 || link->llc_confirm_rkey_rc)
		return -EFAULT;
	return 0;
}