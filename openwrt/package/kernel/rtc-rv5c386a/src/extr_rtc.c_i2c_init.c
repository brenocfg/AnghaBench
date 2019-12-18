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
 int /*<<< orphan*/  gpio_set_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scl_index ; 
 int /*<<< orphan*/  sclhi () ; 
 int /*<<< orphan*/  sda_index ; 
 int /*<<< orphan*/  sdahi () ; 

__attribute__((used)) static void i2c_init(void)
{
    /* no gpio_control for EXTIF */
	// ssb_gpio_control(&ssb, sda_mask | scl_mask, 0);

   gpio_set_value(sda_index, 0);
   gpio_set_value(scl_index, 0);
	sdahi();
	sclhi();
}