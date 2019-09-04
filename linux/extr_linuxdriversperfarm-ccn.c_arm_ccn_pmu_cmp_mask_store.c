#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;
struct device_attribute {TYPE_1__ attr; } ;
struct device {int dummy; } ;
struct arm_ccn {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/ * arm_ccn_pmu_get_cmp_mask (struct arm_ccn*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_get_drvdata (struct device*) ; 
 int kstrtoull (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct arm_ccn* pmu_to_arm_ccn (int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t arm_ccn_pmu_cmp_mask_store(struct device *dev,
		struct device_attribute *attr, const char *buf, size_t count)
{
	struct arm_ccn *ccn = pmu_to_arm_ccn(dev_get_drvdata(dev));
	u64 *mask = arm_ccn_pmu_get_cmp_mask(ccn, attr->attr.name);
	int err = -EINVAL;

	if (mask)
		err = kstrtoull(buf, 0, mask);

	return err ? err : count;
}