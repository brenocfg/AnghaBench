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

/* Variables and functions */
 int /*<<< orphan*/  _irq_pin ; 
 scalar_t__ platform_gpio_read (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int isTouching() {
  return (platform_gpio_read(_irq_pin) == 0);
}