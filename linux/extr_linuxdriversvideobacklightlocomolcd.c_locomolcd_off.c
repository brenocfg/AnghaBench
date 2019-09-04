#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  parent; } ;
struct TYPE_4__ {TYPE_1__ dev; scalar_t__ mapbase; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOCOMO_GPIO_LCD_MOD ; 
 int /*<<< orphan*/  LOCOMO_GPIO_LCD_VEE_ON ; 
 int /*<<< orphan*/  LOCOMO_GPIO_LCD_VSHA_ON ; 
 int /*<<< orphan*/  LOCOMO_GPIO_LCD_VSHD_ON ; 
 scalar_t__ LOCOMO_TC ; 
 int /*<<< orphan*/  locomo_gpio_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  locomo_writel (int,scalar_t__) ; 
 TYPE_2__* locomolcd_dev ; 
 int /*<<< orphan*/  mdelay (int) ; 

__attribute__((used)) static void locomolcd_off(int comadj)
{
	/* TFTCRST=1 | CPSOUT=1 | CPSEN = 0 */
	locomo_writel(0x06, locomolcd_dev->mapbase + LOCOMO_TC);
	mdelay(1);

	locomo_gpio_write(locomolcd_dev->dev.parent, LOCOMO_GPIO_LCD_VSHA_ON, 0);
	mdelay(110);

	locomo_gpio_write(locomolcd_dev->dev.parent, LOCOMO_GPIO_LCD_VEE_ON, 0);
	mdelay(700);

	/* TFTCRST=0 | CPSOUT=0 | CPSEN = 0 */
	locomo_writel(0, locomolcd_dev->mapbase + LOCOMO_TC);
	locomo_gpio_write(locomolcd_dev->dev.parent, LOCOMO_GPIO_LCD_MOD, 0);
	locomo_gpio_write(locomolcd_dev->dev.parent, LOCOMO_GPIO_LCD_VSHD_ON, 0);
}