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
struct rtllib_device {int scanning_continue; int actscanning; int /*<<< orphan*/  scan_mutex; int /*<<< orphan*/  softmac_scan_wq; scalar_t__ scan_watch_dog; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rtllib_softmac_stop_scan(struct rtllib_device *ieee)
{
	mutex_lock(&ieee->scan_mutex);
	ieee->scan_watch_dog = 0;
	if (ieee->scanning_continue == 1) {
		ieee->scanning_continue = 0;
		ieee->actscanning = false;

		cancel_delayed_work_sync(&ieee->softmac_scan_wq);
	}

	mutex_unlock(&ieee->scan_mutex);
}