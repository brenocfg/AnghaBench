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
struct smc_link {int /*<<< orphan*/  llc_delete_rkey_mutex; scalar_t__ llc_delete_rkey_rc; int /*<<< orphan*/  llc_delete_rkey; } ;
struct smc_buf_desc {int dummy; } ;

/* Variables and functions */
 int EFAULT ; 
 int /*<<< orphan*/  SMC_LLC_WAIT_TIME ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reinit_completion (int /*<<< orphan*/ *) ; 
 int smc_llc_send_delete_rkey (struct smc_link*,struct smc_buf_desc*) ; 
 int wait_for_completion_interruptible_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int smc_llc_do_delete_rkey(struct smc_link *link,
			   struct smc_buf_desc *rmb_desc)
{
	int rc;

	mutex_lock(&link->llc_delete_rkey_mutex);
	reinit_completion(&link->llc_delete_rkey);
	rc = smc_llc_send_delete_rkey(link, rmb_desc);
	if (rc)
		goto out;
	/* receive DELETE RKEY response from server over RoCE fabric */
	rc = wait_for_completion_interruptible_timeout(&link->llc_delete_rkey,
						       SMC_LLC_WAIT_TIME);
	if (rc <= 0 || link->llc_delete_rkey_rc)
		rc = -EFAULT;
	else
		rc = 0;
out:
	mutex_unlock(&link->llc_delete_rkey_mutex);
	return rc;
}