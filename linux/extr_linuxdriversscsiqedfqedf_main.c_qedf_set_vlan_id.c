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
struct qedf_ctx {int vlan_id; int prio; int /*<<< orphan*/  dbg_ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  QEDF_INFO (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  QEDF_LOG_DISC ; 
 int VLAN_PRIO_SHIFT ; 

void qedf_set_vlan_id(struct qedf_ctx *qedf, int vlan_id)
{
	qedf->vlan_id = vlan_id;
	qedf->vlan_id |= qedf->prio << VLAN_PRIO_SHIFT;
	QEDF_INFO(&(qedf->dbg_ctx), QEDF_LOG_DISC, "Setting vlan_id=%04x "
		   "prio=%d.\n", vlan_id, qedf->prio);
}