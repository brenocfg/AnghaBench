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
struct sx150x_pinctrl {TYPE_1__* data; } ;
struct device {int dummy; } ;
struct TYPE_2__ {unsigned int reg_irq_src; unsigned int reg_data; } ;

/* Variables and functions */
 struct sx150x_pinctrl* i2c_get_clientdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  to_i2c_client (struct device*) ; 

__attribute__((used)) static bool sx150x_reg_volatile(struct device *dev, unsigned int reg)
{
	struct sx150x_pinctrl *pctl = i2c_get_clientdata(to_i2c_client(dev));

	return reg == pctl->data->reg_irq_src || reg == pctl->data->reg_data;
}