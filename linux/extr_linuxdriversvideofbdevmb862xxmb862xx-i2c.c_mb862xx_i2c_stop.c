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
struct mb862xxfb_par {scalar_t__ i2c_rs; } ;
struct i2c_adapter {struct mb862xxfb_par* algo_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  GC_I2C_BCR ; 
 int /*<<< orphan*/  GC_I2C_CCR ; 
 int /*<<< orphan*/  I2C_DISABLE ; 
 int /*<<< orphan*/  I2C_STOP ; 
 int /*<<< orphan*/  i2c ; 
 int /*<<< orphan*/  outreg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mb862xx_i2c_stop(struct i2c_adapter *adap)
{
	struct mb862xxfb_par *par = adap->algo_data;

	outreg(i2c, GC_I2C_BCR, I2C_STOP);
	outreg(i2c, GC_I2C_CCR, I2C_DISABLE);
	par->i2c_rs = 0;
}