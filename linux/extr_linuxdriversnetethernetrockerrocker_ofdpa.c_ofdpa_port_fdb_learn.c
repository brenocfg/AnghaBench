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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct ofdpa_port {int /*<<< orphan*/  pport; } ;
struct ofdpa_fdb_learn_work {int flags; int /*<<< orphan*/  work; int /*<<< orphan*/  vid; int /*<<< orphan*/  addr; struct ofdpa_port* ofdpa_port; } ;
typedef  enum rocker_of_dpa_table_id { ____Placeholder_rocker_of_dpa_table_id } rocker_of_dpa_table_id ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int OFDPA_OP_FLAG_REFRESH ; 
 int /*<<< orphan*/  ROCKER_GROUP_L2_INTERFACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ROCKER_GROUP_NONE ; 
 int ROCKER_OF_DPA_TABLE_ID_ACL_POLICY ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 struct ofdpa_fdb_learn_work* kzalloc (int,int /*<<< orphan*/ ) ; 
 int ofdpa_flow_tbl_bridge (struct ofdpa_port*,int,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ofdpa_port_fdb_learn_work ; 
 scalar_t__ ofdpa_port_is_bridged (struct ofdpa_port*) ; 
 int /*<<< orphan*/  ofdpa_port_vlan_to_vid (struct ofdpa_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ofdpa_port_fdb_learn(struct ofdpa_port *ofdpa_port,
				int flags, const u8 *addr, __be16 vlan_id)
{
	struct ofdpa_fdb_learn_work *lw;
	enum rocker_of_dpa_table_id goto_tbl =
			ROCKER_OF_DPA_TABLE_ID_ACL_POLICY;
	u32 out_pport = ofdpa_port->pport;
	u32 tunnel_id = 0;
	u32 group_id = ROCKER_GROUP_NONE;
	bool copy_to_cpu = false;
	int err;

	if (ofdpa_port_is_bridged(ofdpa_port))
		group_id = ROCKER_GROUP_L2_INTERFACE(vlan_id, out_pport);

	if (!(flags & OFDPA_OP_FLAG_REFRESH)) {
		err = ofdpa_flow_tbl_bridge(ofdpa_port, flags, addr,
					    NULL, vlan_id, tunnel_id, goto_tbl,
					    group_id, copy_to_cpu);
		if (err)
			return err;
	}

	if (!ofdpa_port_is_bridged(ofdpa_port))
		return 0;

	lw = kzalloc(sizeof(*lw), GFP_ATOMIC);
	if (!lw)
		return -ENOMEM;

	INIT_WORK(&lw->work, ofdpa_port_fdb_learn_work);

	lw->ofdpa_port = ofdpa_port;
	lw->flags = flags;
	ether_addr_copy(lw->addr, addr);
	lw->vid = ofdpa_port_vlan_to_vid(ofdpa_port, vlan_id);

	schedule_work(&lw->work);
	return 0;
}