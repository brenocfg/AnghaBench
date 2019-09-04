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
struct led_classdev {int dummy; } ;
struct gb_lights_blink_request {void* time_off_ms; void* time_on_ms; int /*<<< orphan*/  channel_id; int /*<<< orphan*/  light_id; } ;
struct gb_connection {struct gb_bundle* bundle; } ;
struct gb_channel {int active; int /*<<< orphan*/  lock; int /*<<< orphan*/  id; TYPE_1__* light; scalar_t__ releasing; } ;
struct gb_bundle {int dummy; } ;
typedef  int /*<<< orphan*/  req ;
struct TYPE_2__ {int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int EINVAL ; 
 int ESHUTDOWN ; 
 int /*<<< orphan*/  GB_LIGHTS_TYPE_SET_BLINK ; 
 void* cpu_to_le16 (unsigned long) ; 
 int gb_operation_sync (struct gb_connection*,int /*<<< orphan*/ ,struct gb_lights_blink_request*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int gb_pm_runtime_get_sync (struct gb_bundle*) ; 
 int /*<<< orphan*/  gb_pm_runtime_put_autosuspend (struct gb_bundle*) ; 
 struct gb_channel* get_channel_from_cdev (struct led_classdev*) ; 
 struct gb_connection* get_conn_from_channel (struct gb_channel*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int gb_blink_set(struct led_classdev *cdev, unsigned long *delay_on,
			unsigned long *delay_off)
{
	struct gb_channel *channel = get_channel_from_cdev(cdev);
	struct gb_connection *connection = get_conn_from_channel(channel);
	struct gb_bundle *bundle = connection->bundle;
	struct gb_lights_blink_request req;
	bool old_active;
	int ret;

	if (channel->releasing)
		return -ESHUTDOWN;

	if (!delay_on || !delay_off)
		return -EINVAL;

	mutex_lock(&channel->lock);
	ret = gb_pm_runtime_get_sync(bundle);
	if (ret < 0)
		goto out_unlock;

	old_active = channel->active;

	req.light_id = channel->light->id;
	req.channel_id = channel->id;
	req.time_on_ms = cpu_to_le16(*delay_on);
	req.time_off_ms = cpu_to_le16(*delay_off);

	ret = gb_operation_sync(connection, GB_LIGHTS_TYPE_SET_BLINK, &req,
				sizeof(req), NULL, 0);
	if (ret < 0)
		goto out_pm_put;

	if (*delay_on)
		channel->active = true;
	else
		channel->active = false;

	/* we need to keep module alive when turning to active state */
	if (!old_active && channel->active)
		goto out_unlock;

	/*
	 * on the other hand if going to inactive we still hold a reference and
	 * need to put it, so we could go to suspend.
	 */
	if (old_active && !channel->active)
		gb_pm_runtime_put_autosuspend(bundle);

out_pm_put:
	gb_pm_runtime_put_autosuspend(bundle);
out_unlock:
	mutex_unlock(&channel->lock);

	return ret;
}