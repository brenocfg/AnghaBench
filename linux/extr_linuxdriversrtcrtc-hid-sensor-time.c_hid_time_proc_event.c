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
struct hid_time_state {int /*<<< orphan*/  comp_last_time; int /*<<< orphan*/  lock_last_time; int /*<<< orphan*/  time_buf; int /*<<< orphan*/  last_time; } ;
struct hid_sensor_hub_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 struct hid_time_state* platform_get_drvdata (void*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int hid_time_proc_event(struct hid_sensor_hub_device *hsdev,
				unsigned usage_id, void *priv)
{
	unsigned long flags;
	struct hid_time_state *time_state = platform_get_drvdata(priv);

	spin_lock_irqsave(&time_state->lock_last_time, flags);
	time_state->last_time = time_state->time_buf;
	spin_unlock_irqrestore(&time_state->lock_last_time, flags);
	complete(&time_state->comp_last_time);
	return 0;
}