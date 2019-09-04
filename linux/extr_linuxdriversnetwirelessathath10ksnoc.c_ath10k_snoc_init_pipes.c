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
struct ath10k {int dummy; } ;

/* Variables and functions */
 int CE_COUNT ; 
 int ath10k_ce_init_pipe (struct ath10k*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ath10k_err (struct ath10k*,char*,int,int) ; 
 int /*<<< orphan*/ * host_ce_config_wlan ; 

__attribute__((used)) static int ath10k_snoc_init_pipes(struct ath10k *ar)
{
	int i, ret;

	for (i = 0; i < CE_COUNT; i++) {
		ret = ath10k_ce_init_pipe(ar, i, &host_ce_config_wlan[i]);
		if (ret) {
			ath10k_err(ar, "failed to initialize copy engine pipe %d: %d\n",
				   i, ret);
			return ret;
		}
	}

	return 0;
}