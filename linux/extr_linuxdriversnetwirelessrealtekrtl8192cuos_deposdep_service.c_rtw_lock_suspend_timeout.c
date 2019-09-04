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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */

inline void rtw_lock_suspend_timeout(u32 timeout_ms)
{
	#ifdef CONFIG_WAKELOCK
	wake_lock_timeout(&rtw_suspend_lock, rtw_ms_to_systime(timeout_ms));
	#elif defined(CONFIG_ANDROID_POWER)
	android_lock_suspend_auto_expire(&rtw_suspend_lock, rtw_ms_to_systime(timeout_ms));
	#endif
}