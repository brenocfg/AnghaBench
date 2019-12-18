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
struct nfit_test_sec {int /*<<< orphan*/  ext_state; int /*<<< orphan*/  state; } ;
struct device {int dummy; } ;
struct TYPE_2__ {struct device dev; } ;
struct nfit_test {TYPE_1__ pdev; } ;
struct nd_intel_get_security_state {int /*<<< orphan*/  state; int /*<<< orphan*/  extended_state; scalar_t__ status; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int /*<<< orphan*/ ) ; 
 struct nfit_test_sec* dimm_sec_info ; 

__attribute__((used)) static int nd_intel_test_cmd_security_status(struct nfit_test *t,
		struct nd_intel_get_security_state *nd_cmd,
		unsigned int buf_len, int dimm)
{
	struct device *dev = &t->pdev.dev;
	struct nfit_test_sec *sec = &dimm_sec_info[dimm];

	nd_cmd->status = 0;
	nd_cmd->state = sec->state;
	nd_cmd->extended_state = sec->ext_state;
	dev_dbg(dev, "security state (%#x) returned\n", nd_cmd->state);

	return 0;
}