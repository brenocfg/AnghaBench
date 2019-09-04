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
typedef  scalar_t__ u32 ;
struct nsp_gpio {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IO_CTRL ; 
 int /*<<< orphan*/  NSP_GPIO_SLEW_RATE_EN ; 
 int /*<<< orphan*/  nsp_set_bit (struct nsp_gpio*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int) ; 

__attribute__((used)) static int nsp_gpio_set_slew(struct nsp_gpio *chip, unsigned gpio, u32 slew)
{
	if (slew)
		nsp_set_bit(chip, IO_CTRL, NSP_GPIO_SLEW_RATE_EN, gpio, true);
	else
		nsp_set_bit(chip, IO_CTRL, NSP_GPIO_SLEW_RATE_EN, gpio, false);

	return 0;
}