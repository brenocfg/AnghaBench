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
struct qpnp_tm_chip {scalar_t__ subtype; } ;

/* Variables and functions */
 int /*<<< orphan*/  QPNP_TM_REG_STATUS ; 
 scalar_t__ QPNP_TM_SUBTYPE_GEN1 ; 
 int STATUS_GEN1_STAGE_MASK ; 
 int STATUS_GEN2_STATE_MASK ; 
 int STATUS_GEN2_STATE_SHIFT ; 
 int qpnp_tm_read (struct qpnp_tm_chip*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int qpnp_tm_get_temp_stage(struct qpnp_tm_chip *chip)
{
	int ret;
	u8 reg = 0;

	ret = qpnp_tm_read(chip, QPNP_TM_REG_STATUS, &reg);
	if (ret < 0)
		return ret;

	if (chip->subtype == QPNP_TM_SUBTYPE_GEN1)
		ret = reg & STATUS_GEN1_STAGE_MASK;
	else
		ret = (reg & STATUS_GEN2_STATE_MASK) >> STATUS_GEN2_STATE_SHIFT;

	return ret;
}