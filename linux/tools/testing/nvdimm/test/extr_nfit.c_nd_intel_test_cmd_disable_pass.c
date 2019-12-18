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
struct nd_intel_disable_passphrase {int /*<<< orphan*/  status; int /*<<< orphan*/  passphrase; } ;

/* Variables and functions */
 int /*<<< orphan*/  ND_INTEL_PASSPHRASE_SIZE ; 
 int ND_INTEL_SEC_STATE_ENABLED ; 
 int ND_INTEL_SEC_STATE_FROZEN ; 
 int /*<<< orphan*/  ND_INTEL_STATUS_INVALID_PASS ; 
 int /*<<< orphan*/  ND_INTEL_STATUS_INVALID_STATE ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*) ; 
 struct nfit_test_sec* dimm_sec_info ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nd_intel_test_cmd_disable_pass(struct nfit_test *t,
		struct nd_intel_disable_passphrase *nd_cmd,
		unsigned int buf_len, int dimm)
{
	struct device *dev = &t->pdev.dev;
	struct nfit_test_sec *sec = &dimm_sec_info[dimm];

	if (!(sec->state & ND_INTEL_SEC_STATE_ENABLED) ||
			(sec->state & ND_INTEL_SEC_STATE_FROZEN)) {
		nd_cmd->status = ND_INTEL_STATUS_INVALID_STATE;
		dev_dbg(dev, "disable passphrase: wrong security state\n");
	} else if (memcmp(nd_cmd->passphrase, sec->passphrase,
				ND_INTEL_PASSPHRASE_SIZE) != 0) {
		nd_cmd->status = ND_INTEL_STATUS_INVALID_PASS;
		dev_dbg(dev, "disable passphrase: wrong passphrase\n");
	} else {
		memset(sec->passphrase, 0, ND_INTEL_PASSPHRASE_SIZE);
		sec->state = 0;
		dev_dbg(dev, "disable passphrase: done\n");
	}

	return 0;
}