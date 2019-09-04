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
struct nvdimm {int /*<<< orphan*/  flags; int /*<<< orphan*/  cmd_mask; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int ENOTTY ; 
 int ENXIO ; 
 int /*<<< orphan*/  NDD_ALIASING ; 
 int /*<<< orphan*/  ND_CMD_GET_CONFIG_DATA ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct nvdimm* to_nvdimm (struct device*) ; 

int nvdimm_check_config_data(struct device *dev)
{
	struct nvdimm *nvdimm = to_nvdimm(dev);

	if (!nvdimm->cmd_mask ||
	    !test_bit(ND_CMD_GET_CONFIG_DATA, &nvdimm->cmd_mask)) {
		if (test_bit(NDD_ALIASING, &nvdimm->flags))
			return -ENXIO;
		else
			return -ENOTTY;
	}

	return 0;
}