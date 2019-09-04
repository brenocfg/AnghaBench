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
struct iwl_mvm {unsigned int max_amsdu_len; } ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int IEEE80211_MAX_MPDU_LEN_VHT_11454 ; 
 int kstrtouint (char*,int /*<<< orphan*/ ,unsigned int*) ; 

__attribute__((used)) static ssize_t iwl_dbgfs_max_amsdu_len_write(struct iwl_mvm *mvm,
					     char *buf, size_t count,
					     loff_t *ppos)
{
	unsigned int max_amsdu_len;
	int ret;

	ret = kstrtouint(buf, 0, &max_amsdu_len);
	if (ret)
		return ret;

	if (max_amsdu_len > IEEE80211_MAX_MPDU_LEN_VHT_11454)
		return -EINVAL;
	mvm->max_amsdu_len = max_amsdu_len;

	return count;
}