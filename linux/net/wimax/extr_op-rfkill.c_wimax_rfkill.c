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
struct wimax_dev {int rf_sw; int rf_hw; int /*<<< orphan*/  mutex; int /*<<< orphan*/  rfkill; } ;
struct device {int dummy; } ;
typedef  enum wimax_rf_state { ____Placeholder_wimax_rf_state } wimax_rf_state ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEDIUM ; 
#define  WIMAX_RF_OFF 130 
#define  WIMAX_RF_ON 129 
#define  WIMAX_RF_QUERY 128 
 int __wimax_rf_toggle_radio (struct wimax_dev*,int) ; 
 int /*<<< orphan*/  d_fnend (int,struct device*,char*,struct wimax_dev*,int,int) ; 
 int /*<<< orphan*/  d_fnstart (int,struct device*,char*,struct wimax_dev*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rfkill_set_sw_state (int /*<<< orphan*/ ,int) ; 
 int wimax_dev_is_ready (struct wimax_dev*) ; 
 struct device* wimax_dev_to_dev (struct wimax_dev*) ; 

int wimax_rfkill(struct wimax_dev *wimax_dev, enum wimax_rf_state state)
{
	int result;
	struct device *dev = wimax_dev_to_dev(wimax_dev);

	d_fnstart(3, dev, "(wimax_dev %p state %u)\n", wimax_dev, state);
	mutex_lock(&wimax_dev->mutex);
	result = wimax_dev_is_ready(wimax_dev);
	if (result < 0) {
		/* While initializing, < 1.4.3 wimax-tools versions use
		 * this call to check if the device is a valid WiMAX
		 * device; so we allow it to proceed always,
		 * considering the radios are all off. */
		if (result == -ENOMEDIUM && state == WIMAX_RF_QUERY)
			result = WIMAX_RF_OFF << 1 | WIMAX_RF_OFF;
		goto error_not_ready;
	}
	switch (state) {
	case WIMAX_RF_ON:
	case WIMAX_RF_OFF:
		result = __wimax_rf_toggle_radio(wimax_dev, state);
		if (result < 0)
			goto error;
		rfkill_set_sw_state(wimax_dev->rfkill, state == WIMAX_RF_OFF);
		break;
	case WIMAX_RF_QUERY:
		break;
	default:
		result = -EINVAL;
		goto error;
	}
	result = wimax_dev->rf_sw << 1 | wimax_dev->rf_hw;
error:
error_not_ready:
	mutex_unlock(&wimax_dev->mutex);
	d_fnend(3, dev, "(wimax_dev %p state %u) = %d\n",
		wimax_dev, state, result);
	return result;
}