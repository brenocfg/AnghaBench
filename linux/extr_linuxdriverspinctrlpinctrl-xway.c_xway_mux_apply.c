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
struct pinctrl_dev {int dummy; } ;
struct ltq_pinmux_info {int /*<<< orphan*/ * membase; } ;

/* Variables and functions */
 int /*<<< orphan*/  GPIO3_ALT1 ; 
 int /*<<< orphan*/  GPIO_ALT0 (int) ; 
 int /*<<< orphan*/  GPIO_ALT1 (int) ; 
 int MUX_ALT0 ; 
 int MUX_ALT1 ; 
 int PORT (int) ; 
 int PORT3 ; 
 int /*<<< orphan*/  PORT_PIN (int) ; 
 int /*<<< orphan*/  gpio_clearbit (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_setbit (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ltq_pinmux_info* pinctrl_dev_get_drvdata (struct pinctrl_dev*) ; 

__attribute__((used)) static inline int xway_mux_apply(struct pinctrl_dev *pctrldev,
				int pin, int mux)
{
	struct ltq_pinmux_info *info = pinctrl_dev_get_drvdata(pctrldev);
	int port = PORT(pin);
	u32 alt1_reg = GPIO_ALT1(pin);

	if (port == PORT3)
		alt1_reg = GPIO3_ALT1;

	if (mux & MUX_ALT0)
		gpio_setbit(info->membase[0], GPIO_ALT0(pin), PORT_PIN(pin));
	else
		gpio_clearbit(info->membase[0], GPIO_ALT0(pin), PORT_PIN(pin));

	if (mux & MUX_ALT1)
		gpio_setbit(info->membase[0], alt1_reg, PORT_PIN(pin));
	else
		gpio_clearbit(info->membase[0], alt1_reg, PORT_PIN(pin));

	return 0;
}