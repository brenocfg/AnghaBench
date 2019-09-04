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
typedef  int u32 ;
struct iscsi_tpg_attrib {int default_erl; } ;
struct iscsi_portal_group {int /*<<< orphan*/  tpgt; struct iscsi_tpg_attrib tpg_attrib; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 

int iscsit_ta_default_erl(
	struct iscsi_portal_group *tpg,
	u32 default_erl)
{
	struct iscsi_tpg_attrib *a = &tpg->tpg_attrib;

	if ((default_erl != 0) && (default_erl != 1) && (default_erl != 2)) {
		pr_err("Illegal value for default_erl: %u\n", default_erl);
		return -EINVAL;
	}

	a->default_erl = default_erl;
	pr_debug("iSCSI_TPG[%hu] - DefaultERL: %u\n", tpg->tpgt, a->default_erl);

	return 0;
}