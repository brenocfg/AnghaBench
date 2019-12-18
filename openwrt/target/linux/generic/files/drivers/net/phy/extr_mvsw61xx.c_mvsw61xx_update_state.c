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
typedef  int u16 ;
struct switch_dev {int ports; int vlans; } ;
struct mvsw61xx_state {int mirror_rx; int source_port; int monitor_port; int mirror_tx; TYPE_1__* ports; scalar_t__ vlan_enabled; int /*<<< orphan*/  registered; } ;
struct TYPE_2__ {int mask; int qmode; int pvid; int fdb; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONTROL1 ; 
 int /*<<< orphan*/  CONTROL2 ; 
 int EINVAL ; 
 int /*<<< orphan*/  MONITOR_CTRL ; 
 int MV_8021Q_MODE_DISABLE ; 
 int MV_8021Q_MODE_MASK ; 
 int MV_8021Q_MODE_SHIFT ; 
 int MV_8021Q_VLAN_ONLY ; 
 int MV_FDB_HI_MASK ; 
 int MV_FDB_HI_SHIFT ; 
 int MV_FDB_LO_SHIFT ; 
 int /*<<< orphan*/  MV_GLOBAL2REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MV_GLOBALREG (int /*<<< orphan*/ ) ; 
 int MV_MIRROR_RX_DEST_MASK ; 
 int MV_MIRROR_RX_DEST_SHIFT ; 
 int MV_MIRROR_RX_SRC_MASK ; 
 int MV_MIRROR_RX_SRC_SHIFT ; 
 int MV_MIRROR_TX_DEST_MASK ; 
 int MV_MIRROR_TX_DEST_SHIFT ; 
 int MV_MIRROR_TX_SRC_MASK ; 
 int MV_MIRROR_TX_SRC_SHIFT ; 
 int /*<<< orphan*/  MV_PORTREG (int /*<<< orphan*/ ,int) ; 
 int MV_PVID_MASK ; 
 int /*<<< orphan*/  SDET_POLARITY ; 
 int /*<<< orphan*/  VLANID ; 
 int /*<<< orphan*/  VLANMAP ; 
 struct mvsw61xx_state* get_state (struct switch_dev*) ; 
 int /*<<< orphan*/  mvsw61xx_vlan_port_config (struct switch_dev*,int) ; 
 int /*<<< orphan*/  mvsw61xx_vtu_program (struct switch_dev*) ; 
 int sr16 (struct switch_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sw16 (struct switch_dev*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int mvsw61xx_update_state(struct switch_dev *dev)
{
	struct mvsw61xx_state *state = get_state(dev);
	int i;
	u16 reg;

	if (!state->registered)
		return -EINVAL;

	/*
	 * Set 802.1q-only mode if vlan_enabled is true.
	 *
	 * Without this, even if 802.1q is enabled for
	 * a port/VLAN, it still depends on the port-based
	 * VLAN mask being set.
	 *
	 * With this setting, port-based VLANs are still
	 * functional, provided the VID is not in the VTU.
	 */
	reg = sr16(dev, MV_GLOBAL2REG(SDET_POLARITY));

	if (state->vlan_enabled)
		reg |= MV_8021Q_VLAN_ONLY;
	else
		reg &= ~MV_8021Q_VLAN_ONLY;

	sw16(dev, MV_GLOBAL2REG(SDET_POLARITY), reg);

	/*
	 * Set port-based VLAN masks on each port
	 * based only on VLAN definitions known to
	 * the driver (i.e. in state).
	 *
	 * This means any pre-existing port mapping is
	 * wiped out once our driver is initialized.
	 */
	for (i = 0; i < dev->ports; i++) {
		state->ports[i].mask = 0;
		state->ports[i].qmode = MV_8021Q_MODE_DISABLE;
	}

	for (i = 0; i < dev->vlans; i++)
		mvsw61xx_vlan_port_config(dev, i);

	for (i = 0; i < dev->ports; i++) {
		reg = sr16(dev, MV_PORTREG(VLANID, i)) & ~MV_PVID_MASK;
		reg |= state->ports[i].pvid;
		sw16(dev, MV_PORTREG(VLANID, i), reg);

		state->ports[i].mask &= ~(1 << i);

		/* set default forwarding DB number and port mask */
		reg = sr16(dev, MV_PORTREG(CONTROL1, i)) & ~MV_FDB_HI_MASK;
		reg |= (state->ports[i].fdb >> MV_FDB_HI_SHIFT) &
			MV_FDB_HI_MASK;
		sw16(dev, MV_PORTREG(CONTROL1, i), reg);

		reg = ((state->ports[i].fdb & 0xf) << MV_FDB_LO_SHIFT) |
			state->ports[i].mask;
		sw16(dev, MV_PORTREG(VLANMAP, i), reg);

		reg = sr16(dev, MV_PORTREG(CONTROL2, i)) &
			~MV_8021Q_MODE_MASK;
		reg |= state->ports[i].qmode << MV_8021Q_MODE_SHIFT;
		sw16(dev, MV_PORTREG(CONTROL2, i), reg);
	}

	mvsw61xx_vtu_program(dev);

	/* port mirroring */
	/* reset all mirror registers */
	for (i = 0; i < dev->ports; i++) {
		reg = sr16(dev, MV_PORTREG(CONTROL2, i));
		reg &= ~(MV_MIRROR_RX_SRC_MASK | MV_MIRROR_TX_SRC_MASK);
		sw16(dev, MV_PORTREG(CONTROL2, i), reg);
	}
	reg = sr16(dev, MV_GLOBALREG(MONITOR_CTRL));
	reg |= MV_MIRROR_RX_DEST_MASK | MV_MIRROR_TX_DEST_MASK;
	sw16(dev, MV_GLOBALREG(MONITOR_CTRL), reg);

	/* now enable mirroring if necessary */
	if (state->mirror_rx) {
		/* set ingress monitor source */
		reg = sr16(dev, MV_PORTREG(CONTROL2, state->source_port)) & ~MV_MIRROR_RX_SRC_MASK;
		reg |= state->mirror_rx << MV_MIRROR_RX_SRC_SHIFT;
		sw16(dev, MV_PORTREG(CONTROL2, state->source_port), reg);
		/* set ingress monitor destination */
		reg = sr16(dev, MV_GLOBALREG(MONITOR_CTRL)) & ~MV_MIRROR_RX_DEST_MASK;
		reg |= state->monitor_port << MV_MIRROR_RX_DEST_SHIFT;
		sw16(dev, MV_GLOBALREG(MONITOR_CTRL), reg);
	}

	if (state->mirror_tx) {
		/* set egress monitor source */
		reg = sr16(dev, MV_PORTREG(CONTROL2, state->source_port)) & ~MV_MIRROR_TX_SRC_MASK;
		reg |= state->mirror_tx << MV_MIRROR_TX_SRC_SHIFT;
		sw16(dev, MV_PORTREG(CONTROL2, state->source_port), reg);
		/* set egress monitor destination */
		reg = sr16(dev, MV_GLOBALREG(MONITOR_CTRL)) & ~MV_MIRROR_TX_DEST_MASK;
		reg |= state->monitor_port << MV_MIRROR_TX_DEST_SHIFT;
		sw16(dev, MV_GLOBALREG(MONITOR_CTRL), reg);
	}

	return 0;
}