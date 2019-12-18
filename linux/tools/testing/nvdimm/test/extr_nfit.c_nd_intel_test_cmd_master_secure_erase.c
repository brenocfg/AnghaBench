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
struct nfit_test_sec {int ext_state; scalar_t__ state; int /*<<< orphan*/  passphrase; int /*<<< orphan*/  master_passphrase; } ;
struct device {int dummy; } ;
struct TYPE_2__ {struct device dev; } ;
struct nfit_test {TYPE_1__ pdev; } ;
struct nd_intel_master_secure_erase {int /*<<< orphan*/  status; int /*<<< orphan*/  passphrase; } ;

/* Variables and functions */
 int /*<<< orphan*/  ND_INTEL_PASSPHRASE_SIZE ; 
 int ND_INTEL_SEC_ESTATE_ENABLED ; 
 int ND_INTEL_SEC_ESTATE_PLIMIT ; 
 int /*<<< orphan*/  ND_INTEL_STATUS_INVALID_PASS ; 
 int /*<<< orphan*/  ND_INTEL_STATUS_INVALID_STATE ; 
 int /*<<< orphan*/  ND_INTEL_STATUS_NOT_SUPPORTED ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*) ; 
 struct nfit_test_sec* dimm_sec_info ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nd_intel_test_cmd_master_secure_erase(struct nfit_test *t,
		struct nd_intel_master_secure_erase *nd_cmd,
		unsigned int buf_len, int dimm)
{
	struct device *dev = &t->pdev.dev;
	struct nfit_test_sec *sec = &dimm_sec_info[dimm];

	if (!(sec->ext_state & ND_INTEL_SEC_ESTATE_ENABLED)) {
		nd_cmd->status = ND_INTEL_STATUS_NOT_SUPPORTED;
		dev_dbg(dev, "master secure erase: in wrong state\n");
	} else if (sec->ext_state & ND_INTEL_SEC_ESTATE_PLIMIT) {
		nd_cmd->status = ND_INTEL_STATUS_INVALID_STATE;
		dev_dbg(dev, "master secure erase: in wrong security state\n");
	} else if (memcmp(nd_cmd->passphrase, sec->master_passphrase,
				ND_INTEL_PASSPHRASE_SIZE) != 0) {
		nd_cmd->status = ND_INTEL_STATUS_INVALID_PASS;
		dev_dbg(dev, "master secure erase: wrong passphrase\n");
	} else {
		/* we do not erase master state passphrase ever */
		sec->ext_state = ND_INTEL_SEC_ESTATE_ENABLED;
		memset(sec->passphrase, 0, ND_INTEL_PASSPHRASE_SIZE);
		sec->state = 0;
		dev_dbg(dev, "master secure erase: done\n");
	}

	return 0;
}