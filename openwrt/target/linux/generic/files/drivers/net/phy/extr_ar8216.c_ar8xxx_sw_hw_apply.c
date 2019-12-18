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
typedef  int u8 ;
struct switch_dev {int ports; } ;
struct ar8xxx_priv {int* vlan_table; int /*<<< orphan*/  reg_mutex; int /*<<< orphan*/ * vlan_id; int /*<<< orphan*/  init; struct ar8xxx_chip* chip; } ;
struct ar8xxx_chip {scalar_t__ reg_arl_ctrl; int /*<<< orphan*/  (* set_mirror_regs ) (struct ar8xxx_priv*) ;int /*<<< orphan*/  (* setup_port ) (struct ar8xxx_priv*,int,int) ;int /*<<< orphan*/  (* vtu_load_vlan ) (struct ar8xxx_priv*,int /*<<< orphan*/ ,int) ;int /*<<< orphan*/  (* vtu_flush ) (struct ar8xxx_priv*) ;} ;
typedef  int /*<<< orphan*/  portmask ;

/* Variables and functions */
 int AR8216_PORT_CPU ; 
 int AR8X16_MAX_PORTS ; 
 int AR8X16_MAX_VLANS ; 
 int /*<<< orphan*/  ar8xxx_set_age_time (struct ar8xxx_priv*,scalar_t__) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct ar8xxx_priv*) ; 
 int /*<<< orphan*/  stub2 (struct ar8xxx_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub3 (struct ar8xxx_priv*,int,int) ; 
 int /*<<< orphan*/  stub4 (struct ar8xxx_priv*) ; 
 struct ar8xxx_priv* swdev_to_ar8xxx (struct switch_dev*) ; 

int
ar8xxx_sw_hw_apply(struct switch_dev *dev)
{
	struct ar8xxx_priv *priv = swdev_to_ar8xxx(dev);
	const struct ar8xxx_chip *chip = priv->chip;
	u8 portmask[AR8X16_MAX_PORTS];
	int i, j;

	mutex_lock(&priv->reg_mutex);
	/* flush all vlan translation unit entries */
	priv->chip->vtu_flush(priv);

	memset(portmask, 0, sizeof(portmask));
	if (!priv->init) {
		/* calculate the port destination masks and load vlans
		 * into the vlan translation unit */
		for (j = 0; j < AR8X16_MAX_VLANS; j++) {
			u8 vp = priv->vlan_table[j];

			if (!vp)
				continue;

			for (i = 0; i < dev->ports; i++) {
				u8 mask = (1 << i);
				if (vp & mask)
					portmask[i] |= vp & ~mask;
			}

			chip->vtu_load_vlan(priv, priv->vlan_id[j],
					    priv->vlan_table[j]);
		}
	} else {
		/* vlan disabled:
		 * isolate all ports, but connect them to the cpu port */
		for (i = 0; i < dev->ports; i++) {
			if (i == AR8216_PORT_CPU)
				continue;

			portmask[i] = 1 << AR8216_PORT_CPU;
			portmask[AR8216_PORT_CPU] |= (1 << i);
		}
	}

	/* update the port destination mask registers and tag settings */
	for (i = 0; i < dev->ports; i++) {
		chip->setup_port(priv, i, portmask[i]);
	}

	chip->set_mirror_regs(priv);

	/* set age time */
	if (chip->reg_arl_ctrl)
		ar8xxx_set_age_time(priv, chip->reg_arl_ctrl);

	mutex_unlock(&priv->reg_mutex);
	return 0;
}