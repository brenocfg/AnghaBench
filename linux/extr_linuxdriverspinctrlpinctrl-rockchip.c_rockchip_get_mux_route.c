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
typedef  int /*<<< orphan*/  u32 ;
struct rockchip_pinctrl {struct rockchip_pin_ctrl* ctrl; } ;
struct rockchip_pin_ctrl {int niomux_routes; struct rockchip_mux_route_data* iomux_routes; } ;
struct rockchip_pin_bank {scalar_t__ bank_num; struct rockchip_pinctrl* drvdata; } ;
struct rockchip_mux_route_data {scalar_t__ bank_num; int pin; int func; int /*<<< orphan*/  route_val; int /*<<< orphan*/  route_offset; } ;

/* Variables and functions */

__attribute__((used)) static bool rockchip_get_mux_route(struct rockchip_pin_bank *bank, int pin,
				   int mux, u32 *reg, u32 *value)
{
	struct rockchip_pinctrl *info = bank->drvdata;
	struct rockchip_pin_ctrl *ctrl = info->ctrl;
	struct rockchip_mux_route_data *data;
	int i;

	for (i = 0; i < ctrl->niomux_routes; i++) {
		data = &ctrl->iomux_routes[i];
		if ((data->bank_num == bank->bank_num) &&
		    (data->pin == pin) && (data->func == mux))
			break;
	}

	if (i >= ctrl->niomux_routes)
		return false;

	*reg = data->route_offset;
	*value = data->route_val;

	return true;
}