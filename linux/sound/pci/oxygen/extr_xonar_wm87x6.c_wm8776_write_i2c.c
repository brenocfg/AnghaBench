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
struct oxygen {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  I2C_DEVICE_WM8776 ; 
 int /*<<< orphan*/  oxygen_write_i2c (struct oxygen*,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 

__attribute__((used)) static void wm8776_write_i2c(struct oxygen *chip,
			     unsigned int reg, unsigned int value)
{
	oxygen_write_i2c(chip, I2C_DEVICE_WM8776,
			 (reg << 1) | (value >> 8), value);
}