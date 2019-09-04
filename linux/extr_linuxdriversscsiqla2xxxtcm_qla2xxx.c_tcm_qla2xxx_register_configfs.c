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
struct TYPE_2__ {int /*<<< orphan*/  release; int /*<<< orphan*/  machine; int /*<<< orphan*/  sysname; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  QLA2XXX_VERSION ; 
 int /*<<< orphan*/  WQ_MEM_RECLAIM ; 
 int /*<<< orphan*/  alloc_workqueue (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int target_register_template (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  target_unregister_template (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tcm_qla2xxx_free_wq ; 
 int /*<<< orphan*/  tcm_qla2xxx_npiv_ops ; 
 int /*<<< orphan*/  tcm_qla2xxx_ops ; 
 TYPE_1__* utsname () ; 

__attribute__((used)) static int tcm_qla2xxx_register_configfs(void)
{
	int ret;

	pr_debug("TCM QLOGIC QLA2XXX fabric module %s on %s/%s on %s\n",
	    QLA2XXX_VERSION, utsname()->sysname,
	    utsname()->machine, utsname()->release);

	ret = target_register_template(&tcm_qla2xxx_ops);
	if (ret)
		return ret;

	ret = target_register_template(&tcm_qla2xxx_npiv_ops);
	if (ret)
		goto out_fabric;

	tcm_qla2xxx_free_wq = alloc_workqueue("tcm_qla2xxx_free",
						WQ_MEM_RECLAIM, 0);
	if (!tcm_qla2xxx_free_wq) {
		ret = -ENOMEM;
		goto out_fabric_npiv;
	}

	return 0;

out_fabric_npiv:
	target_unregister_template(&tcm_qla2xxx_npiv_ops);
out_fabric:
	target_unregister_template(&tcm_qla2xxx_ops);
	return ret;
}