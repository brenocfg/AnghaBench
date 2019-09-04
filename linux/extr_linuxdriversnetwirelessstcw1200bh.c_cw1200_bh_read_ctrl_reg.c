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
typedef  int /*<<< orphan*/  u16 ;
struct cw1200_common {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ST90TDS_CONTROL_REG_ID ; 
 int cw1200_reg_read_16 (struct cw1200_common*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static int cw1200_bh_read_ctrl_reg(struct cw1200_common *priv,
					  u16 *ctrl_reg)
{
	int ret;

	ret = cw1200_reg_read_16(priv,
			ST90TDS_CONTROL_REG_ID, ctrl_reg);
	if (ret) {
		ret = cw1200_reg_read_16(priv,
				ST90TDS_CONTROL_REG_ID, ctrl_reg);
		if (ret)
			pr_err("[BH] Failed to read control register.\n");
	}

	return ret;
}