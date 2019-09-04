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
struct bq2415x_device {int /*<<< orphan*/ * timer_error; } ;

/* Variables and functions */
 int /*<<< orphan*/  BQ2415X_REG_CONTROL ; 
 int /*<<< orphan*/  BQ2415X_REG_CURRENT ; 
 int /*<<< orphan*/  BQ2415X_REG_STATUS ; 
 int /*<<< orphan*/  BQ2415X_REG_VOLTAGE ; 
 int /*<<< orphan*/  BQ2415X_RESET_CONTROL ; 
 int /*<<< orphan*/  BQ2415X_RESET_CURRENT ; 
 int /*<<< orphan*/  BQ2415X_RESET_STATUS ; 
 int /*<<< orphan*/  BQ2415X_RESET_VOLTAGE ; 
 int /*<<< orphan*/  bq2415x_i2c_write (struct bq2415x_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bq2415x_reset_chip(struct bq2415x_device *bq)
{
	bq2415x_i2c_write(bq, BQ2415X_REG_CURRENT, BQ2415X_RESET_CURRENT);
	bq2415x_i2c_write(bq, BQ2415X_REG_VOLTAGE, BQ2415X_RESET_VOLTAGE);
	bq2415x_i2c_write(bq, BQ2415X_REG_CONTROL, BQ2415X_RESET_CONTROL);
	bq2415x_i2c_write(bq, BQ2415X_REG_STATUS, BQ2415X_RESET_STATUS);
	bq->timer_error = NULL;
}