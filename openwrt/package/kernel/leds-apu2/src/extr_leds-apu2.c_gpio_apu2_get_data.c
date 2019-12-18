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
typedef  int u32 ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 int GPIO_BIT_READ ; 
 int /*<<< orphan*/ * gpio_addr ; 
 int ioread32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int gpio_apu2_get_data (struct gpio_chip *chip, unsigned offset)
{
	u32 val;

	val = ioread32 (gpio_addr[offset]);

	return (val >> GPIO_BIT_READ) & 1;
}