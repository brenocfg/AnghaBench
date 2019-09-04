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
typedef  int u8 ;
struct watchdog_device {int /*<<< orphan*/  timeout; } ;
struct kempld_wdt_data {struct kempld_device_data* pld; } ;
struct kempld_device_data {int dummy; } ;

/* Variables and functions */
 int EACCES ; 
 int /*<<< orphan*/  KEMPLD_WDT_CFG ; 
 int KEMPLD_WDT_CFG_ENABLE ; 
 int /*<<< orphan*/  kempld_get_mutex (struct kempld_device_data*) ; 
 int kempld_read8 (struct kempld_device_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kempld_release_mutex (struct kempld_device_data*) ; 
 int kempld_wdt_set_timeout (struct watchdog_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kempld_write8 (struct kempld_device_data*,int /*<<< orphan*/ ,int) ; 
 struct kempld_wdt_data* watchdog_get_drvdata (struct watchdog_device*) ; 

__attribute__((used)) static int kempld_wdt_start(struct watchdog_device *wdd)
{
	struct kempld_wdt_data *wdt_data = watchdog_get_drvdata(wdd);
	struct kempld_device_data *pld = wdt_data->pld;
	u8 status;
	int ret;

	ret = kempld_wdt_set_timeout(wdd, wdd->timeout);
	if (ret)
		return ret;

	kempld_get_mutex(pld);
	status = kempld_read8(pld, KEMPLD_WDT_CFG);
	status |= KEMPLD_WDT_CFG_ENABLE;
	kempld_write8(pld, KEMPLD_WDT_CFG, status);
	status = kempld_read8(pld, KEMPLD_WDT_CFG);
	kempld_release_mutex(pld);

	/* Check if the watchdog was enabled */
	if (!(status & KEMPLD_WDT_CFG_ENABLE))
		return -EACCES;

	return 0;
}