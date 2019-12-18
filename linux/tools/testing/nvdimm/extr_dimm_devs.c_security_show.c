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
struct TYPE_2__ {int /*<<< orphan*/  flags; } ;
struct nvdimm {TYPE_1__ sec; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  ENOTTY ; 
 int /*<<< orphan*/  NVDIMM_SECURITY_DISABLED ; 
 int /*<<< orphan*/  NVDIMM_SECURITY_LOCKED ; 
 int /*<<< orphan*/  NVDIMM_SECURITY_UNLOCKED ; 
 int /*<<< orphan*/  NVDIMM_USER ; 
 int /*<<< orphan*/  nvdimm_security_flags (struct nvdimm*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (char*,char*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct nvdimm* to_nvdimm (struct device*) ; 

ssize_t security_show(struct device *dev,
		struct device_attribute *attr, char *buf)
{
	struct nvdimm *nvdimm = to_nvdimm(dev);

	/*
	 * For the test version we need to poll the "hardware" in order
	 * to get the updated status for unlock testing.
	 */
	nvdimm->sec.flags = nvdimm_security_flags(nvdimm, NVDIMM_USER);

	if (test_bit(NVDIMM_SECURITY_DISABLED, &nvdimm->sec.flags))
		return sprintf(buf, "disabled\n");
	if (test_bit(NVDIMM_SECURITY_UNLOCKED, &nvdimm->sec.flags))
		return sprintf(buf, "unlocked\n");
	if (test_bit(NVDIMM_SECURITY_LOCKED, &nvdimm->sec.flags))
		return sprintf(buf, "locked\n");
	return -ENOTTY;
}