#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
struct zd_rf {int (* set_channel ) (struct zd_rf*,scalar_t__) ;scalar_t__ channel; } ;
struct TYPE_3__ {int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ MAX_CHANNEL24 ; 
 scalar_t__ MIN_CHANNEL24 ; 
 int /*<<< orphan*/  ZD_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg_f (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  mutex_is_locked (int /*<<< orphan*/ *) ; 
 int stub1 (struct zd_rf*,scalar_t__) ; 
 int /*<<< orphan*/  zd_chip_dev (TYPE_1__*) ; 
 TYPE_1__* zd_rf_to_chip (struct zd_rf*) ; 

int zd_rf_set_channel(struct zd_rf *rf, u8 channel)
{
	int r;

	ZD_ASSERT(mutex_is_locked(&zd_rf_to_chip(rf)->mutex));
	if (channel < MIN_CHANNEL24)
		return -EINVAL;
	if (channel > MAX_CHANNEL24)
		return -EINVAL;
	dev_dbg_f(zd_chip_dev(zd_rf_to_chip(rf)), "channel: %d\n", channel);

	r = rf->set_channel(rf, channel);
	if (r >= 0)
		rf->channel = channel;
	return r;
}