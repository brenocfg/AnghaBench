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
struct ar8xxx_priv {int dummy; } ;

/* Variables and functions */
 int AR8216_ATU_CTRL_AGE_EN ; 
 int AR8216_ATU_CTRL_ARP_EN ; 
 int AR8216_ATU_CTRL_LEARN_CHANGE ; 
 int AR8216_ATU_CTRL_RESERVED ; 
 int /*<<< orphan*/  AR8216_GCTRL_MTU ; 
 int AR8216_GLOBAL_CPUPORT_EN ; 
 int AR8216_GLOBAL_CPUPORT_MIRROR_PORT_S ; 
 int /*<<< orphan*/  AR8216_REG_ATU_CTRL ; 
 int /*<<< orphan*/  AR8216_REG_FLOOD_MASK ; 
 int /*<<< orphan*/  AR8216_REG_GLOBAL_CPUPORT ; 
 int /*<<< orphan*/  AR8216_REG_GLOBAL_CTRL ; 
 int /*<<< orphan*/  AR8216_REG_SERVICE_TAG ; 
 int /*<<< orphan*/  AR8216_REG_TAG_PRIORITY ; 
 int /*<<< orphan*/  AR8216_SERVICE_TAG_M ; 
 int /*<<< orphan*/  AR8236_FM_CPU_BROADCAST_EN ; 
 int /*<<< orphan*/  ar8xxx_reg_set (struct ar8xxx_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ar8xxx_rmw (struct ar8xxx_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ar8xxx_write (struct ar8xxx_priv*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
ar7240sw_init_globals(struct ar8xxx_priv *priv)
{

	/* Enable CPU port, and disable mirror port */
	ar8xxx_write(priv, AR8216_REG_GLOBAL_CPUPORT,
		     AR8216_GLOBAL_CPUPORT_EN |
		     (15 << AR8216_GLOBAL_CPUPORT_MIRROR_PORT_S));

	/* Setup TAG priority mapping */
	ar8xxx_write(priv, AR8216_REG_TAG_PRIORITY, 0xfa50);

	/* Enable ARP frame acknowledge, aging, MAC replacing */
	ar8xxx_write(priv, AR8216_REG_ATU_CTRL,
		AR8216_ATU_CTRL_RESERVED |
		0x2b /* 5 min age time */ |
		AR8216_ATU_CTRL_AGE_EN |
		AR8216_ATU_CTRL_ARP_EN |
		AR8216_ATU_CTRL_LEARN_CHANGE);

	/* Enable Broadcast frames transmitted to the CPU */
	ar8xxx_reg_set(priv, AR8216_REG_FLOOD_MASK,
		       AR8236_FM_CPU_BROADCAST_EN);

	/* setup MTU */
	ar8xxx_rmw(priv, AR8216_REG_GLOBAL_CTRL,
		   AR8216_GCTRL_MTU,
		   AR8216_GCTRL_MTU);

	/* setup Service TAG */
	ar8xxx_rmw(priv, AR8216_REG_SERVICE_TAG, AR8216_SERVICE_TAG_M, 0);
}