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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  work; } ;
struct cxacru_data {int poll_state; TYPE_1__ poll_work; int /*<<< orphan*/  adsl_state_serialize; int /*<<< orphan*/  poll_state_serialize; int /*<<< orphan*/  usbatm; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_NET_ADMIN ; 
 int /*<<< orphan*/  CM_REQUEST_CHIP_ADSL_LINE_START ; 
 int /*<<< orphan*/  CM_REQUEST_CHIP_ADSL_LINE_STOP ; 
#define  CXPOLL_POLLING 131 
#define  CXPOLL_SHUTDOWN 130 
#define  CXPOLL_STOPPED 129 
#define  CXPOLL_STOPPING 128 
 int EACCES ; 
 int EINVAL ; 
 int EIO ; 
 int ENODEV ; 
 int ERESTARTSYS ; 
 int /*<<< orphan*/  atm_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 int cxacru_cm (struct cxacru_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cxacru_poll_status (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 scalar_t__ mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int sscanf (char const*,char*,char*) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  to_usb_interface (struct device*) ; 
 struct cxacru_data* to_usbatm_driver_data (int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t adsl_state_store(struct device *dev,
	struct device_attribute *attr, const char *buf, size_t count)
{
	struct cxacru_data *instance = to_usbatm_driver_data(
			to_usb_interface(dev));
	int ret;
	int poll = -1;
	char str_cmd[8];
	int len = strlen(buf);

	if (!capable(CAP_NET_ADMIN))
		return -EACCES;

	ret = sscanf(buf, "%7s", str_cmd);
	if (ret != 1)
		return -EINVAL;
	ret = 0;

	if (instance == NULL)
		return -ENODEV;

	if (mutex_lock_interruptible(&instance->adsl_state_serialize))
		return -ERESTARTSYS;

	if (!strcmp(str_cmd, "stop") || !strcmp(str_cmd, "restart")) {
		ret = cxacru_cm(instance, CM_REQUEST_CHIP_ADSL_LINE_STOP, NULL, 0, NULL, 0);
		if (ret < 0) {
			atm_err(instance->usbatm, "change adsl state:"
				" CHIP_ADSL_LINE_STOP returned %d\n", ret);

			ret = -EIO;
		} else {
			ret = len;
			poll = CXPOLL_STOPPED;
		}
	}

	/* Line status is only updated every second
	 * and the device appears to only react to
	 * START/STOP every second too. Wait 1.5s to
	 * be sure that restart will have an effect. */
	if (!strcmp(str_cmd, "restart"))
		msleep(1500);

	if (!strcmp(str_cmd, "start") || !strcmp(str_cmd, "restart")) {
		ret = cxacru_cm(instance, CM_REQUEST_CHIP_ADSL_LINE_START, NULL, 0, NULL, 0);
		if (ret < 0) {
			atm_err(instance->usbatm, "change adsl state:"
				" CHIP_ADSL_LINE_START returned %d\n", ret);

			ret = -EIO;
		} else {
			ret = len;
			poll = CXPOLL_POLLING;
		}
	}

	if (!strcmp(str_cmd, "poll")) {
		ret = len;
		poll = CXPOLL_POLLING;
	}

	if (ret == 0) {
		ret = -EINVAL;
		poll = -1;
	}

	if (poll == CXPOLL_POLLING) {
		mutex_lock(&instance->poll_state_serialize);
		switch (instance->poll_state) {
		case CXPOLL_STOPPED:
			/* start polling */
			instance->poll_state = CXPOLL_POLLING;
			break;

		case CXPOLL_STOPPING:
			/* abort stop request */
			instance->poll_state = CXPOLL_POLLING;
			/* fall through */
		case CXPOLL_POLLING:
		case CXPOLL_SHUTDOWN:
			/* don't start polling */
			poll = -1;
		}
		mutex_unlock(&instance->poll_state_serialize);
	} else if (poll == CXPOLL_STOPPED) {
		mutex_lock(&instance->poll_state_serialize);
		/* request stop */
		if (instance->poll_state == CXPOLL_POLLING)
			instance->poll_state = CXPOLL_STOPPING;
		mutex_unlock(&instance->poll_state_serialize);
	}

	mutex_unlock(&instance->adsl_state_serialize);

	if (poll == CXPOLL_POLLING)
		cxacru_poll_status(&instance->poll_work.work);

	return ret;
}