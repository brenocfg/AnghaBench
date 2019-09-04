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
struct rpm_regulator_req {int dummy; } ;
struct qcom_rpm_reg {int /*<<< orphan*/  id; int /*<<< orphan*/  type; int /*<<< orphan*/  rpm; } ;

/* Variables and functions */
 int /*<<< orphan*/  QCOM_SMD_RPM_ACTIVE_STATE ; 
 int qcom_rpm_smd_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct rpm_regulator_req*,size_t) ; 

__attribute__((used)) static int rpm_reg_write_active(struct qcom_rpm_reg *vreg,
				struct rpm_regulator_req *req,
				size_t size)
{
	return qcom_rpm_smd_write(vreg->rpm,
				  QCOM_SMD_RPM_ACTIVE_STATE,
				  vreg->type,
				  vreg->id,
				  req, size);
}