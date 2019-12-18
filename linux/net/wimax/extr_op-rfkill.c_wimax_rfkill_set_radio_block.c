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
struct wimax_dev {scalar_t__ state; int /*<<< orphan*/  mutex; } ;
struct device {int dummy; } ;
typedef  enum wimax_rf_state { ____Placeholder_wimax_rf_state } wimax_rf_state ;

/* Variables and functions */
 int WIMAX_RF_OFF ; 
 int WIMAX_RF_ON ; 
 scalar_t__ __WIMAX_ST_QUIESCING ; 
 int __wimax_rf_toggle_radio (struct wimax_dev*,int) ; 
 int /*<<< orphan*/  d_fnend (int,struct device*,char*,struct wimax_dev*,int,int) ; 
 int /*<<< orphan*/  d_fnstart (int,struct device*,char*,struct wimax_dev*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct device* wimax_dev_to_dev (struct wimax_dev*) ; 

__attribute__((used)) static int wimax_rfkill_set_radio_block(void *data, bool blocked)
{
	int result;
	struct wimax_dev *wimax_dev = data;
	struct device *dev = wimax_dev_to_dev(wimax_dev);
	enum wimax_rf_state rf_state;

	d_fnstart(3, dev, "(wimax_dev %p blocked %u)\n", wimax_dev, blocked);
	rf_state = WIMAX_RF_ON;
	if (blocked)
		rf_state = WIMAX_RF_OFF;
	mutex_lock(&wimax_dev->mutex);
	if (wimax_dev->state <= __WIMAX_ST_QUIESCING)
		result = 0;
	else
		result = __wimax_rf_toggle_radio(wimax_dev, rf_state);
	mutex_unlock(&wimax_dev->mutex);
	d_fnend(3, dev, "(wimax_dev %p blocked %u) = %d\n",
		wimax_dev, blocked, result);
	return result;
}