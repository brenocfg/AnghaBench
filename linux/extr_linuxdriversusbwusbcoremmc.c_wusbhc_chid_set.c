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
struct wusb_ckhdid {int dummy; } ;
struct wusbhc {int /*<<< orphan*/  mutex; int /*<<< orphan*/ * uwb_rc; int /*<<< orphan*/  pal; TYPE_1__* dev; struct wusb_ckhdid chid; scalar_t__ active; } ;
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENODEV ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*) ; 
 scalar_t__ memcmp (struct wusb_ckhdid const*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int uwb_radio_start (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uwb_radio_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * uwb_rc_get_by_grandpa (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uwb_rc_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wusb_ckhdid_zero ; 
 int wusbhc_pal_register (struct wusbhc*) ; 

int wusbhc_chid_set(struct wusbhc *wusbhc, const struct wusb_ckhdid *chid)
{
	int result = 0;

	if (memcmp(chid, &wusb_ckhdid_zero, sizeof(*chid)) == 0)
		chid = NULL;

	mutex_lock(&wusbhc->mutex);
	if (chid) {
		if (wusbhc->active) {
			mutex_unlock(&wusbhc->mutex);
			return -EBUSY;
		}
		wusbhc->chid = *chid;
	}

	/* register with UWB if we haven't already since we are about to start
	    the radio. */
	if ((chid) && (wusbhc->uwb_rc == NULL)) {
		wusbhc->uwb_rc = uwb_rc_get_by_grandpa(wusbhc->dev->parent);
		if (wusbhc->uwb_rc == NULL) {
			result = -ENODEV;
			dev_err(wusbhc->dev,
				"Cannot get associated UWB Host Controller\n");
			goto error_rc_get;
		}

		result = wusbhc_pal_register(wusbhc);
		if (result < 0) {
			dev_err(wusbhc->dev, "Cannot register as a UWB PAL\n");
			goto error_pal_register;
		}
	}
	mutex_unlock(&wusbhc->mutex);

	if (chid)
		result = uwb_radio_start(&wusbhc->pal);
	else if (wusbhc->uwb_rc)
		uwb_radio_stop(&wusbhc->pal);

	return result;

error_pal_register:
	uwb_rc_put(wusbhc->uwb_rc);
	wusbhc->uwb_rc = NULL;
error_rc_get:
	mutex_unlock(&wusbhc->mutex);

	return result;
}