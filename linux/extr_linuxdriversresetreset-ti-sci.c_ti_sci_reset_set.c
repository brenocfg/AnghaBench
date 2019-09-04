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
typedef  int /*<<< orphan*/  u32 ;
struct ti_sci_reset_data {int /*<<< orphan*/  idr; struct ti_sci_handle* sci; } ;
struct ti_sci_reset_control {int /*<<< orphan*/  lock; int /*<<< orphan*/  dev_id; int /*<<< orphan*/  reset_mask; } ;
struct ti_sci_dev_ops {int (* get_device_resets ) (struct ti_sci_handle const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;int (* set_device_resets ) (struct ti_sci_handle const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_2__ {struct ti_sci_dev_ops dev_ops; } ;
struct ti_sci_handle {TYPE_1__ ops; } ;
struct reset_controller_dev {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 struct ti_sci_reset_control* idr_find (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int stub1 (struct ti_sci_handle const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int stub2 (struct ti_sci_handle const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ti_sci_reset_data* to_ti_sci_reset_data (struct reset_controller_dev*) ; 

__attribute__((used)) static int ti_sci_reset_set(struct reset_controller_dev *rcdev,
			    unsigned long id, bool assert)
{
	struct ti_sci_reset_data *data = to_ti_sci_reset_data(rcdev);
	const struct ti_sci_handle *sci = data->sci;
	const struct ti_sci_dev_ops *dev_ops = &sci->ops.dev_ops;
	struct ti_sci_reset_control *control;
	u32 reset_state;
	int ret;

	control = idr_find(&data->idr, id);
	if (!control)
		return -EINVAL;

	mutex_lock(&control->lock);

	ret = dev_ops->get_device_resets(sci, control->dev_id, &reset_state);
	if (ret)
		goto out;

	if (assert)
		reset_state |= control->reset_mask;
	else
		reset_state &= ~control->reset_mask;

	ret = dev_ops->set_device_resets(sci, control->dev_id, reset_state);
out:
	mutex_unlock(&control->lock);

	return ret;
}