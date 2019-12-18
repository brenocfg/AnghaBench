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
struct ar8xxx_priv {int source_port; int monitor_port; scalar_t__ mirror_tx; scalar_t__ mirror_rx; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR8216_GLOBAL_CPUPORT_MIRROR_PORT ; 
 int AR8216_GLOBAL_CPUPORT_MIRROR_PORT_S ; 
 int AR8216_NUM_PORTS ; 
 int /*<<< orphan*/  AR8216_PORT_CTRL_MIRROR_RX ; 
 int /*<<< orphan*/  AR8216_PORT_CTRL_MIRROR_TX ; 
 int /*<<< orphan*/  AR8216_REG_GLOBAL_CPUPORT ; 
 int /*<<< orphan*/  AR8216_REG_PORT_CTRL (int) ; 
 int /*<<< orphan*/  ar8xxx_reg_clear (struct ar8xxx_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ar8xxx_reg_set (struct ar8xxx_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ar8xxx_rmw (struct ar8xxx_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
ar8216_set_mirror_regs(struct ar8xxx_priv *priv)
{
	int port;

	/* reset all mirror registers */
	ar8xxx_rmw(priv, AR8216_REG_GLOBAL_CPUPORT,
		   AR8216_GLOBAL_CPUPORT_MIRROR_PORT,
		   (0xF << AR8216_GLOBAL_CPUPORT_MIRROR_PORT_S));
	for (port = 0; port < AR8216_NUM_PORTS; port++) {
		ar8xxx_reg_clear(priv, AR8216_REG_PORT_CTRL(port),
			   AR8216_PORT_CTRL_MIRROR_RX);

		ar8xxx_reg_clear(priv, AR8216_REG_PORT_CTRL(port),
			   AR8216_PORT_CTRL_MIRROR_TX);
	}

	/* now enable mirroring if necessary */
	if (priv->source_port >= AR8216_NUM_PORTS ||
	    priv->monitor_port >= AR8216_NUM_PORTS ||
	    priv->source_port == priv->monitor_port) {
		return;
	}

	ar8xxx_rmw(priv, AR8216_REG_GLOBAL_CPUPORT,
		   AR8216_GLOBAL_CPUPORT_MIRROR_PORT,
		   (priv->monitor_port << AR8216_GLOBAL_CPUPORT_MIRROR_PORT_S));

	if (priv->mirror_rx)
		ar8xxx_reg_set(priv, AR8216_REG_PORT_CTRL(priv->source_port),
			   AR8216_PORT_CTRL_MIRROR_RX);

	if (priv->mirror_tx)
		ar8xxx_reg_set(priv, AR8216_REG_PORT_CTRL(priv->source_port),
			   AR8216_PORT_CTRL_MIRROR_TX);
}