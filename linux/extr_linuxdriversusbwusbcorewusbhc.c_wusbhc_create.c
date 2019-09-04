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
struct wusbhc {int dnts_num_slots; int dnts_interval; int /*<<< orphan*/  mutex; int /*<<< orphan*/  retry_count; scalar_t__ phy_rate; int /*<<< orphan*/  trust_timeout; } ;

/* Variables and functions */
 scalar_t__ UWB_PHY_RATE_INVALID ; 
 int /*<<< orphan*/  WUSB_RETRY_COUNT_INFINITE ; 
 int /*<<< orphan*/  WUSB_TRUST_TIMEOUT_MS ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int wusbhc_devconnect_create (struct wusbhc*) ; 
 int /*<<< orphan*/  wusbhc_devconnect_destroy (struct wusbhc*) ; 
 int wusbhc_mmcie_create (struct wusbhc*) ; 
 int /*<<< orphan*/  wusbhc_mmcie_destroy (struct wusbhc*) ; 
 int wusbhc_rh_create (struct wusbhc*) ; 
 int /*<<< orphan*/  wusbhc_rh_destroy (struct wusbhc*) ; 
 int wusbhc_sec_create (struct wusbhc*) ; 

int wusbhc_create(struct wusbhc *wusbhc)
{
	int result = 0;

	/* set defaults.  These can be overwritten using sysfs attributes. */
	wusbhc->trust_timeout = WUSB_TRUST_TIMEOUT_MS;
	wusbhc->phy_rate = UWB_PHY_RATE_INVALID - 1;
	wusbhc->dnts_num_slots = 4;
	wusbhc->dnts_interval = 2;
	wusbhc->retry_count = WUSB_RETRY_COUNT_INFINITE;

	mutex_init(&wusbhc->mutex);
	result = wusbhc_mmcie_create(wusbhc);
	if (result < 0)
		goto error_mmcie_create;
	result = wusbhc_devconnect_create(wusbhc);
	if (result < 0)
		goto error_devconnect_create;
	result = wusbhc_rh_create(wusbhc);
	if (result < 0)
		goto error_rh_create;
	result = wusbhc_sec_create(wusbhc);
	if (result < 0)
		goto error_sec_create;
	return 0;

error_sec_create:
	wusbhc_rh_destroy(wusbhc);
error_rh_create:
	wusbhc_devconnect_destroy(wusbhc);
error_devconnect_create:
	wusbhc_mmcie_destroy(wusbhc);
error_mmcie_create:
	return result;
}