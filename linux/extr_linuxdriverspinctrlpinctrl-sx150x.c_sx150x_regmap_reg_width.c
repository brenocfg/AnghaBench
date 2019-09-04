#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct sx150x_pinctrl {struct sx150x_device_data* data; } ;
struct TYPE_7__ {unsigned int reg_advanced; } ;
struct TYPE_6__ {unsigned int reg_advanced; } ;
struct TYPE_5__ {unsigned int reg_misc; unsigned int reg_clock; unsigned int reg_reset; } ;
struct TYPE_8__ {TYPE_3__ x456; TYPE_2__ x123; TYPE_1__ x789; } ;
struct sx150x_device_data {unsigned int reg_sense; int ngpios; scalar_t__ model; TYPE_4__ pri; } ;

/* Variables and functions */
 scalar_t__ SX150X_123 ; 
 scalar_t__ SX150X_456 ; 
 scalar_t__ SX150X_789 ; 

__attribute__((used)) static int sx150x_regmap_reg_width(struct sx150x_pinctrl *pctl,
				   unsigned int reg)
{
	const struct sx150x_device_data *data = pctl->data;

	if (reg == data->reg_sense) {
		/*
		 * RegSense packs two bits of configuration per GPIO,
		 * so we'd need to read twice as many bits as there
		 * are GPIO in our chip
		 */
		return 2 * data->ngpios;
	} else if ((data->model == SX150X_789 &&
		    (reg == data->pri.x789.reg_misc ||
		     reg == data->pri.x789.reg_clock ||
		     reg == data->pri.x789.reg_reset))
		   ||
		   (data->model == SX150X_123 &&
		    reg == data->pri.x123.reg_advanced)
		   ||
		   (data->model == SX150X_456 &&
		    data->pri.x456.reg_advanced &&
		    reg == data->pri.x456.reg_advanced)) {
		return 8;
	} else {
		return data->ngpios;
	}
}