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
struct ath10k_htt {int target_version_major; int /*<<< orphan*/  target_version_minor; struct ath10k* ar; } ;
struct ath10k {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH10K_DBG_BOOT ; 
 int ENOTSUPP ; 
 int /*<<< orphan*/  ath10k_dbg (struct ath10k*,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath10k_err (struct ath10k*,char*,int) ; 

__attribute__((used)) static int ath10k_htt_verify_version(struct ath10k_htt *htt)
{
	struct ath10k *ar = htt->ar;

	ath10k_dbg(ar, ATH10K_DBG_BOOT, "htt target version %d.%d\n",
		   htt->target_version_major, htt->target_version_minor);

	if (htt->target_version_major != 2 &&
	    htt->target_version_major != 3) {
		ath10k_err(ar, "unsupported htt major version %d. supported versions are 2 and 3\n",
			   htt->target_version_major);
		return -ENOTSUPP;
	}

	return 0;
}