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
struct nd_intel_set_passphrase {scalar_t__ status; int /*<<< orphan*/  new_pass; int /*<<< orphan*/  old_pass; } ;

/* Variables and functions */
 int /*<<< orphan*/  ND_INTEL_PASSPHRASE_SIZE ; 
 int ND_INTEL_SEC_STATE_ENABLED ; 
 int ND_INTEL_SEC_STATE_FROZEN ; 
 scalar_t__ ND_INTEL_STATUS_INVALID_PASS ; 
 scalar_t__ ND_INTEL_STATUS_INVALID_STATE ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*) ; 
 struct nfit_test_sec* dimm_sec_info ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nd_intel_test_cmd_set_pass(struct nfit_test *t,
		struct nd_intel_set_passphrase *nd_cmd,
		unsigned int buf_len, int dimm)
{
	struct device *dev = &t->pdev.dev;
	struct nfit_test_sec *sec = &dimm_sec_info[dimm];

	if (sec->state & ND_INTEL_SEC_STATE_FROZEN) {
		nd_cmd->status = ND_INTEL_STATUS_INVALID_STATE;
		dev_dbg(dev, "set passphrase: wrong security state\n");
	} else if (memcmp(nd_cmd->old_pass, sec->passphrase,
				ND_INTEL_PASSPHRASE_SIZE) != 0) {
		nd_cmd->status = ND_INTEL_STATUS_INVALID_PASS;
		dev_dbg(dev, "set passphrase: wrong passphrase\n");
	} else {
		memcpy(sec->passphrase, nd_cmd->new_pass,
				ND_INTEL_PASSPHRASE_SIZE);
		sec->state |= ND_INTEL_SEC_STATE_ENABLED;
		nd_cmd->status = 0;
		dev_dbg(dev, "passphrase updated\n");
	}

	return 0;
}