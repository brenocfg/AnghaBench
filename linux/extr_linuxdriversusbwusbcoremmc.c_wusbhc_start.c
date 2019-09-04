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
struct wusbhc {int (* set_num_dnts ) (struct wusbhc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  dnts_num_slots; int /*<<< orphan*/  dnts_interval; int /*<<< orphan*/ * uwb_rc; int /*<<< orphan*/ * wuie_host_info; struct device* dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int stub1 (struct wusbhc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int wusbhc_devconnect_start (struct wusbhc*) ; 
 int /*<<< orphan*/  wusbhc_devconnect_stop (struct wusbhc*) ; 
 int wusbhc_mmc_start (struct wusbhc*) ; 
 int wusbhc_rsv_establish (struct wusbhc*) ; 
 int /*<<< orphan*/  wusbhc_rsv_terminate (struct wusbhc*) ; 
 int wusbhc_sec_start (struct wusbhc*) ; 
 int /*<<< orphan*/  wusbhc_sec_stop (struct wusbhc*) ; 

int wusbhc_start(struct wusbhc *wusbhc)
{
	int result;
	struct device *dev = wusbhc->dev;

	WARN_ON(wusbhc->wuie_host_info != NULL);
	BUG_ON(wusbhc->uwb_rc == NULL);

	result = wusbhc_rsv_establish(wusbhc);
	if (result < 0) {
		dev_err(dev, "cannot establish cluster reservation: %d\n",
			result);
		goto error_rsv_establish;
	}

	result = wusbhc_devconnect_start(wusbhc);
	if (result < 0) {
		dev_err(dev, "error enabling device connections: %d\n",
			result);
		goto error_devconnect_start;
	}

	result = wusbhc_sec_start(wusbhc);
	if (result < 0) {
		dev_err(dev, "error starting security in the HC: %d\n",
			result);
		goto error_sec_start;
	}

	result = wusbhc->set_num_dnts(wusbhc, wusbhc->dnts_interval,
		wusbhc->dnts_num_slots);
	if (result < 0) {
		dev_err(dev, "Cannot set DNTS parameters: %d\n", result);
		goto error_set_num_dnts;
	}
	result = wusbhc_mmc_start(wusbhc);
	if (result < 0) {
		dev_err(dev, "error starting wusbch: %d\n", result);
		goto error_wusbhc_start;
	}

	return 0;

error_wusbhc_start:
	wusbhc_sec_stop(wusbhc);
error_set_num_dnts:
error_sec_start:
	wusbhc_devconnect_stop(wusbhc);
error_devconnect_start:
	wusbhc_rsv_terminate(wusbhc);
error_rsv_establish:
	return result;
}