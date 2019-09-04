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
struct bbc_i2c_bus {int own; int clock; scalar_t__ i2c_control_regs; } ;

/* Variables and functions */
 int I2C_PCF_ES1 ; 
 int I2C_PCF_IDLE ; 
 int I2C_PCF_PIN ; 
 int /*<<< orphan*/  writeb (int,scalar_t__) ; 

__attribute__((used)) static void reset_one_i2c(struct bbc_i2c_bus *bp)
{
	writeb(I2C_PCF_PIN, bp->i2c_control_regs + 0x0);
	writeb(bp->own, bp->i2c_control_regs + 0x1);
	writeb(I2C_PCF_PIN | I2C_PCF_ES1, bp->i2c_control_regs + 0x0);
	writeb(bp->clock, bp->i2c_control_regs + 0x1);
	writeb(I2C_PCF_IDLE, bp->i2c_control_regs + 0x0);
}