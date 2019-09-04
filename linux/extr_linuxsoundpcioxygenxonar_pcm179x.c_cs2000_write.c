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
typedef  size_t u8 ;
struct xonar_pcm179x {size_t* cs2000_regs; } ;
struct oxygen {struct xonar_pcm179x* model_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  I2C_DEVICE_CS2000 ; 
 int /*<<< orphan*/  oxygen_write_i2c (struct oxygen*,int /*<<< orphan*/ ,size_t,size_t) ; 

__attribute__((used)) static void cs2000_write(struct oxygen *chip, u8 reg, u8 value)
{
	struct xonar_pcm179x *data = chip->model_data;

	oxygen_write_i2c(chip, I2C_DEVICE_CS2000, reg, value);
	data->cs2000_regs[reg] = value;
}