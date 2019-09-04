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
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/ * arm_ccn_pmu_get_cmp_mask (struct arm_ccn*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_get_drvdata (struct device*) ; 
 struct arm_ccn* pmu_to_arm_ccn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t arm_ccn_pmu_cmp_mask_show(struct device *dev,
		struct device_attribute *attr, char *buf)
{
	struct arm_ccn *ccn = pmu_to_arm_ccn(dev_get_drvdata(dev));
	u64 *mask = arm_ccn_pmu_get_cmp_mask(ccn, attr->attr.name);

	return mask ? snprintf(buf, PAGE_SIZE, "0x%016llx\n", *mask) : -EINVAL;
}