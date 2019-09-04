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

/* Variables and functions */

inline void rtw_suspend_lock_init()
{
	#ifdef CONFIG_WAKELOCK
	wake_lock_init(&rtw_suspend_lock, WAKE_LOCK_SUSPEND, RTW_SUSPEND_LOCK_NAME);
	#elif defined(CONFIG_ANDROID_POWER)
	android_init_suspend_lock(&rtw_suspend_lock);
	#endif
}