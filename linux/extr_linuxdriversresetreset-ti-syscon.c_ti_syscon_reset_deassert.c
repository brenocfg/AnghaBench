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
struct ti_syscon_reset_data {unsigned long nr_controls; int /*<<< orphan*/  regmap; struct ti_syscon_reset_control* controls; } ;
struct ti_syscon_reset_control {int flags; int /*<<< orphan*/  deassert_offset; int /*<<< orphan*/  deassert_bit; } ;
struct reset_controller_dev {int dummy; } ;

/* Variables and functions */
 unsigned int BIT (int /*<<< orphan*/ ) ; 
 int DEASSERT_NONE ; 
 int DEASSERT_SET ; 
 int EINVAL ; 
 int ENOTSUPP ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 struct ti_syscon_reset_data* to_ti_syscon_reset_data (struct reset_controller_dev*) ; 

__attribute__((used)) static int ti_syscon_reset_deassert(struct reset_controller_dev *rcdev,
				    unsigned long id)
{
	struct ti_syscon_reset_data *data = to_ti_syscon_reset_data(rcdev);
	struct ti_syscon_reset_control *control;
	unsigned int mask, value;

	if (id >= data->nr_controls)
		return -EINVAL;

	control = &data->controls[id];

	if (control->flags & DEASSERT_NONE)
		return -ENOTSUPP; /* deassert not supported for this reset */

	mask = BIT(control->deassert_bit);
	value = (control->flags & DEASSERT_SET) ? mask : 0x0;

	return regmap_update_bits(data->regmap, control->deassert_offset, mask, value);
}