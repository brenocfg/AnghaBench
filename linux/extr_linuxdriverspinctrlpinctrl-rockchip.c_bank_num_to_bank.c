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
struct rockchip_pinctrl {TYPE_1__* ctrl; } ;
struct rockchip_pin_bank {unsigned int bank_num; } ;
struct TYPE_2__ {int nr_banks; struct rockchip_pin_bank* pin_banks; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 struct rockchip_pin_bank* ERR_PTR (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct rockchip_pin_bank *bank_num_to_bank(
					struct rockchip_pinctrl *info,
					unsigned num)
{
	struct rockchip_pin_bank *b = info->ctrl->pin_banks;
	int i;

	for (i = 0; i < info->ctrl->nr_banks; i++, b++) {
		if (b->bank_num == num)
			return b;
	}

	return ERR_PTR(-EINVAL);
}