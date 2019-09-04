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
typedef  int /*<<< orphan*/  u32 ;
struct rpm_regulator_req {void* value; void* nbytes; void* key; } ;
struct regulator_dev {int dummy; } ;
struct qcom_rpm_reg {int uV; } ;
typedef  int /*<<< orphan*/  req ;

/* Variables and functions */
 int RPM_KEY_UV ; 
 void* cpu_to_le32 (int) ; 
 struct qcom_rpm_reg* rdev_get_drvdata (struct regulator_dev*) ; 
 int rpm_reg_write_active (struct qcom_rpm_reg*,struct rpm_regulator_req*,int) ; 

__attribute__((used)) static int rpm_reg_set_voltage(struct regulator_dev *rdev,
			       int min_uV,
			       int max_uV,
			       unsigned *selector)
{
	struct qcom_rpm_reg *vreg = rdev_get_drvdata(rdev);
	struct rpm_regulator_req req;
	int ret = 0;

	req.key = cpu_to_le32(RPM_KEY_UV);
	req.nbytes = cpu_to_le32(sizeof(u32));
	req.value = cpu_to_le32(min_uV);

	ret = rpm_reg_write_active(vreg, &req, sizeof(req));
	if (!ret)
		vreg->uV = min_uV;

	return ret;
}