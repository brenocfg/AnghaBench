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
struct nfit_test_sec {int state; int /*<<< orphan*/  passphrase; } ;
struct device {int dummy; } ;
struct TYPE_2__ {struct device dev; } ;
struct nfit_test {TYPE_1__ pdev; } ;
struct nd_intel_unlock_unit {int status; int /*<<< orphan*/  passphrase; } ;

/* Variables and functions */
 int /*<<< orphan*/  ND_INTEL_PASSPHRASE_SIZE ; 
 int ND_INTEL_SEC_STATE_ENABLED ; 
 int ND_INTEL_SEC_STATE_FROZEN ; 
 int ND_INTEL_SEC_STATE_LOCKED ; 
 int ND_INTEL_STATUS_INVALID_PASS ; 
 int ND_INTEL_STATUS_INVALID_STATE ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,...) ; 
 struct nfit_test_sec* dimm_sec_info ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nd_intel_test_cmd_unlock_unit(struct nfit_test *t,
		struct nd_intel_unlock_unit *nd_cmd,
		unsigned int buf_len, int dimm)
{
	struct device *dev = &t->pdev.dev;
	struct nfit_test_sec *sec = &dimm_sec_info[dimm];

	if (!(sec->state & ND_INTEL_SEC_STATE_LOCKED) ||
			(sec->state & ND_INTEL_SEC_STATE_FROZEN)) {
		nd_cmd->status = ND_INTEL_STATUS_INVALID_STATE;
		dev_dbg(dev, "unlock unit: invalid state: %#x\n",
				sec->state);
	} else if (memcmp(nd_cmd->passphrase, sec->passphrase,
				ND_INTEL_PASSPHRASE_SIZE) != 0) {
		nd_cmd->status = ND_INTEL_STATUS_INVALID_PASS;
		dev_dbg(dev, "unlock unit: invalid passphrase\n");
	} else {
		nd_cmd->status = 0;
		sec->state = ND_INTEL_SEC_STATE_ENABLED;
		dev_dbg(dev, "Unit unlocked\n");
	}

	dev_dbg(dev, "unlocking status returned: %#x\n", nd_cmd->status);
	return 0;
}