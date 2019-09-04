#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  service_ready; } ;
struct ath10k {TYPE_1__ wmi; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int /*<<< orphan*/  WMI_SERVICE_READY_TIMEOUT_HZ ; 
 unsigned long wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int ath10k_wmi_wait_for_service_ready(struct ath10k *ar)
{
	unsigned long time_left;

	time_left = wait_for_completion_timeout(&ar->wmi.service_ready,
						WMI_SERVICE_READY_TIMEOUT_HZ);
	if (!time_left)
		return -ETIMEDOUT;
	return 0;
}