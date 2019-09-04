#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ath10k_fw_stats {int dummy; } ;
struct TYPE_4__ {TYPE_1__* ops; } ;
struct ath10k {TYPE_2__ wmi; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* fw_stats_fill ) (struct ath10k*,struct ath10k_fw_stats*,char*) ;} ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  stub1 (struct ath10k*,struct ath10k_fw_stats*,char*) ; 

__attribute__((used)) static inline int
ath10k_wmi_fw_stats_fill(struct ath10k *ar, struct ath10k_fw_stats *fw_stats,
			 char *buf)
{
	if (!ar->wmi.ops->fw_stats_fill)
		return -EOPNOTSUPP;

	ar->wmi.ops->fw_stats_fill(ar, fw_stats, buf);
	return 0;
}