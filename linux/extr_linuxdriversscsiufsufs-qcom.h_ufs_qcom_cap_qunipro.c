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
struct ufs_qcom_host {int caps; } ;

/* Variables and functions */
 int UFS_QCOM_CAP_QUNIPRO ; 

__attribute__((used)) static inline bool ufs_qcom_cap_qunipro(struct ufs_qcom_host *host)
{
	if (host->caps & UFS_QCOM_CAP_QUNIPRO)
		return true;
	else
		return false;
}