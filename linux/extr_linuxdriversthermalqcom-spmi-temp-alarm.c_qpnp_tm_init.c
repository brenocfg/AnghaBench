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
typedef  int u8 ;
struct qpnp_tm_chip {int thresh; int stage; scalar_t__ subtype; scalar_t__ temp; } ;

/* Variables and functions */
 int ALARM_CTRL_FORCE_ENABLE ; 
 scalar_t__ DEFAULT_TEMP ; 
 int /*<<< orphan*/  QPNP_TM_REG_ALARM_CTRL ; 
 int /*<<< orphan*/  QPNP_TM_REG_SHUTDOWN_CTRL1 ; 
 scalar_t__ QPNP_TM_SUBTYPE_GEN1 ; 
 int SHUTDOWN_CTRL1_OVERRIDE_MASK ; 
 int SHUTDOWN_CTRL1_THRESHOLD_MASK ; 
 unsigned int TEMP_STAGE_STEP ; 
 scalar_t__ TEMP_THRESH_MIN ; 
 unsigned int TEMP_THRESH_STEP ; 
 unsigned int THRESH_MIN ; 
 unsigned int* alarm_state_map ; 
 int qpnp_tm_get_temp_stage (struct qpnp_tm_chip*) ; 
 int qpnp_tm_read (struct qpnp_tm_chip*,int /*<<< orphan*/ ,int*) ; 
 int qpnp_tm_write (struct qpnp_tm_chip*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int qpnp_tm_init(struct qpnp_tm_chip *chip)
{
	unsigned int stage;
	int ret;
	u8 reg = 0;

	ret = qpnp_tm_read(chip, QPNP_TM_REG_SHUTDOWN_CTRL1, &reg);
	if (ret < 0)
		return ret;

	chip->thresh = reg & SHUTDOWN_CTRL1_THRESHOLD_MASK;
	chip->temp = DEFAULT_TEMP;

	ret = qpnp_tm_get_temp_stage(chip);
	if (ret < 0)
		return ret;
	chip->stage = ret;

	stage = chip->subtype == QPNP_TM_SUBTYPE_GEN1
		? chip->stage : alarm_state_map[chip->stage];

	if (stage)
		chip->temp = chip->thresh * TEMP_THRESH_STEP +
			     (stage - 1) * TEMP_STAGE_STEP +
			     TEMP_THRESH_MIN;

	/*
	 * Set threshold and disable software override of stage 2 and 3
	 * shutdowns.
	 */
	chip->thresh = THRESH_MIN;
	reg &= ~(SHUTDOWN_CTRL1_OVERRIDE_MASK | SHUTDOWN_CTRL1_THRESHOLD_MASK);
	reg |= chip->thresh & SHUTDOWN_CTRL1_THRESHOLD_MASK;
	ret = qpnp_tm_write(chip, QPNP_TM_REG_SHUTDOWN_CTRL1, reg);
	if (ret < 0)
		return ret;

	/* Enable the thermal alarm PMIC module in always-on mode. */
	reg = ALARM_CTRL_FORCE_ENABLE;
	ret = qpnp_tm_write(chip, QPNP_TM_REG_ALARM_CTRL, reg);

	return ret;
}