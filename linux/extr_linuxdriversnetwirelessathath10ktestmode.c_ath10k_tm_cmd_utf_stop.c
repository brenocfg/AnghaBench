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
struct nlattr {int dummy; } ;
struct ath10k {scalar_t__ state; int /*<<< orphan*/  conf_mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH10K_DBG_TESTMODE ; 
 scalar_t__ ATH10K_STATE_UTF ; 
 int ENETDOWN ; 
 int /*<<< orphan*/  __ath10k_tm_cmd_utf_stop (struct ath10k*) ; 
 int /*<<< orphan*/  ath10k_dbg (struct ath10k*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ath10k_info (struct ath10k*,char*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ath10k_tm_cmd_utf_stop(struct ath10k *ar, struct nlattr *tb[])
{
	int ret;

	ath10k_dbg(ar, ATH10K_DBG_TESTMODE, "testmode cmd utf stop\n");

	mutex_lock(&ar->conf_mutex);

	if (ar->state != ATH10K_STATE_UTF) {
		ret = -ENETDOWN;
		goto out;
	}

	__ath10k_tm_cmd_utf_stop(ar);

	ret = 0;

	ath10k_info(ar, "UTF firmware stopped\n");

out:
	mutex_unlock(&ar->conf_mutex);
	return ret;
}