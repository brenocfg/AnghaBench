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
struct nfit_test_sec {int state; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 int ND_INTEL_SEC_STATE_ENABLED ; 
 int ND_INTEL_SEC_STATE_LOCKED ; 
 int dimm_name_to_id (struct device*) ; 
 struct nfit_test_sec* dimm_sec_info ; 

__attribute__((used)) static ssize_t lock_dimm_store(struct device *dev,
		struct device_attribute *attr, const char *buf, size_t size)
{
	int dimm = dimm_name_to_id(dev);
	struct nfit_test_sec *sec = &dimm_sec_info[dimm];

	sec->state = ND_INTEL_SEC_STATE_ENABLED | ND_INTEL_SEC_STATE_LOCKED;
	return size;
}