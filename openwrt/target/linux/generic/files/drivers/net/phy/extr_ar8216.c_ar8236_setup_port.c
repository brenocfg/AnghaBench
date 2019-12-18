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
struct ar8xxx_priv {int* vlan_id; size_t* pvid; int vlan_tagged; scalar_t__ vlan; } ;

/* Variables and functions */
 int AR8216_IN_PORT_ONLY ; 
 int AR8216_IN_SECURE ; 
 int AR8216_OUT_ADD_VLAN ; 
 int AR8216_OUT_KEEP ; 
 int AR8216_OUT_STRIP_VLAN ; 
 int AR8216_PORT_CTRL_HEADER ; 
 int AR8216_PORT_CTRL_LEARN ; 
 int AR8216_PORT_CTRL_LEARN_LOCK ; 
 int AR8216_PORT_CTRL_SINGLE_VLAN ; 
 int AR8216_PORT_CTRL_STATE ; 
 int AR8216_PORT_CTRL_STATE_S ; 
 int AR8216_PORT_CTRL_VLAN_MODE ; 
 int AR8216_PORT_CTRL_VLAN_MODE_S ; 
 int AR8216_PORT_STATE_FORWARD ; 
 int /*<<< orphan*/  AR8216_REG_PORT_CTRL (int) ; 
 int AR8236_PORT_VLAN2_MEMBER ; 
 int AR8236_PORT_VLAN2_MEMBER_S ; 
 int AR8236_PORT_VLAN2_VLAN_MODE ; 
 int AR8236_PORT_VLAN2_VLAN_MODE_S ; 
 int AR8236_PORT_VLAN_DEFAULT_ID ; 
 int AR8236_PORT_VLAN_DEFAULT_ID_S ; 
 int /*<<< orphan*/  AR8236_REG_PORT_VLAN (int) ; 
 int /*<<< orphan*/  AR8236_REG_PORT_VLAN2 (int) ; 
 int /*<<< orphan*/  ar8xxx_rmw (struct ar8xxx_priv*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void
ar8236_setup_port(struct ar8xxx_priv *priv, int port, u32 members)
{
	u32 egress, ingress;
	u32 pvid;

	if (priv->vlan) {
		pvid = priv->vlan_id[priv->pvid[port]];
		if (priv->vlan_tagged & (1 << port))
			egress = AR8216_OUT_ADD_VLAN;
		else
			egress = AR8216_OUT_STRIP_VLAN;
		ingress = AR8216_IN_SECURE;
	} else {
		pvid = port;
		egress = AR8216_OUT_KEEP;
		ingress = AR8216_IN_PORT_ONLY;
	}

	ar8xxx_rmw(priv, AR8216_REG_PORT_CTRL(port),
		   AR8216_PORT_CTRL_LEARN | AR8216_PORT_CTRL_VLAN_MODE |
		   AR8216_PORT_CTRL_SINGLE_VLAN | AR8216_PORT_CTRL_STATE |
		   AR8216_PORT_CTRL_HEADER | AR8216_PORT_CTRL_LEARN_LOCK,
		   AR8216_PORT_CTRL_LEARN |
		   (egress << AR8216_PORT_CTRL_VLAN_MODE_S) |
		   (AR8216_PORT_STATE_FORWARD << AR8216_PORT_CTRL_STATE_S));

	ar8xxx_rmw(priv, AR8236_REG_PORT_VLAN(port),
		   AR8236_PORT_VLAN_DEFAULT_ID,
		   (pvid << AR8236_PORT_VLAN_DEFAULT_ID_S));

	ar8xxx_rmw(priv, AR8236_REG_PORT_VLAN2(port),
		   AR8236_PORT_VLAN2_VLAN_MODE |
		   AR8236_PORT_VLAN2_MEMBER,
		   (ingress << AR8236_PORT_VLAN2_VLAN_MODE_S) |
		   (members << AR8236_PORT_VLAN2_MEMBER_S));
}