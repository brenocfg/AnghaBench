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
struct nfit_test_sec {int state; int old_state; int /*<<< orphan*/  ext_state; scalar_t__ overwrite_end_time; } ;
struct device {int dummy; } ;
struct TYPE_2__ {struct device dev; } ;
struct nfit_test {TYPE_1__ pdev; } ;
struct nd_intel_query_overwrite {int /*<<< orphan*/  status; } ;

/* Variables and functions */
 int /*<<< orphan*/  ND_INTEL_SEC_ESTATE_ENABLED ; 
 int ND_INTEL_SEC_STATE_OVERWRITE ; 
 int /*<<< orphan*/  ND_INTEL_STATUS_OQUERY_INPROGRESS ; 
 int /*<<< orphan*/  ND_INTEL_STATUS_OQUERY_SEQUENCE_ERR ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*) ; 
 struct nfit_test_sec* dimm_sec_info ; 
 scalar_t__ time_is_before_jiffies64 (scalar_t__) ; 

__attribute__((used)) static int nd_intel_test_cmd_query_overwrite(struct nfit_test *t,
		struct nd_intel_query_overwrite *nd_cmd,
		unsigned int buf_len, int dimm)
{
	struct device *dev = &t->pdev.dev;
	struct nfit_test_sec *sec = &dimm_sec_info[dimm];

	if (!(sec->state & ND_INTEL_SEC_STATE_OVERWRITE)) {
		nd_cmd->status = ND_INTEL_STATUS_OQUERY_SEQUENCE_ERR;
		return 0;
	}

	if (time_is_before_jiffies64(sec->overwrite_end_time)) {
		sec->overwrite_end_time = 0;
		sec->state = sec->old_state;
		sec->old_state = 0;
		sec->ext_state = ND_INTEL_SEC_ESTATE_ENABLED;
		dev_dbg(dev, "overwrite is complete\n");
	} else
		nd_cmd->status = ND_INTEL_STATUS_OQUERY_INPROGRESS;
	return 0;
}