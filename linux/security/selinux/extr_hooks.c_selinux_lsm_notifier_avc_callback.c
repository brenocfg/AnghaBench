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
typedef  scalar_t__ u32 ;

/* Variables and functions */
 scalar_t__ AVC_CALLBACK_RESET ; 
 int /*<<< orphan*/  LSM_POLICY_CHANGE ; 
 int /*<<< orphan*/  call_blocking_lsm_notifier (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sel_ib_pkey_flush () ; 

__attribute__((used)) static int selinux_lsm_notifier_avc_callback(u32 event)
{
	if (event == AVC_CALLBACK_RESET) {
		sel_ib_pkey_flush();
		call_blocking_lsm_notifier(LSM_POLICY_CHANGE, NULL);
	}

	return 0;
}