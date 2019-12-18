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
struct ar8xxx_priv {struct ar8327_data* chip_data; } ;
struct ar8327_data {int* eee; } ;

/* Variables and functions */
 int AR8327_FWD_CTRL0_CPU_PORT_EN ; 
 int AR8327_FWD_CTRL0_MIRROR_PORT ; 
 int AR8327_FWD_CTRL1_BC_FLOOD_S ; 
 int AR8327_FWD_CTRL1_MC_FLOOD_S ; 
 int AR8327_FWD_CTRL1_UC_FLOOD_S ; 
 int /*<<< orphan*/  AR8327_MAX_FRAME_SIZE_MTU ; 
 int /*<<< orphan*/  AR8327_MODULE_EN_MIB ; 
 int AR8327_PORTS_ALL ; 
 int /*<<< orphan*/  AR8327_REG_FWD_CTRL0 ; 
 int /*<<< orphan*/  AR8327_REG_FWD_CTRL1 ; 
 int /*<<< orphan*/  AR8327_REG_MAX_FRAME_SIZE ; 
 int /*<<< orphan*/  AR8327_REG_MODULE_EN ; 
 int AR8XXX_NUM_PHYS ; 
 int /*<<< orphan*/  ar8xxx_reg_set (struct ar8xxx_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ar8xxx_rmw (struct ar8xxx_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ar8xxx_write (struct ar8xxx_priv*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
ar8327_init_globals(struct ar8xxx_priv *priv)
{
	struct ar8327_data *data = priv->chip_data;
	u32 t;
	int i;

	/* enable CPU port and disable mirror port */
	t = AR8327_FWD_CTRL0_CPU_PORT_EN |
	    AR8327_FWD_CTRL0_MIRROR_PORT;
	ar8xxx_write(priv, AR8327_REG_FWD_CTRL0, t);

	/* forward multicast and broadcast frames to CPU */
	t = (AR8327_PORTS_ALL << AR8327_FWD_CTRL1_UC_FLOOD_S) |
	    (AR8327_PORTS_ALL << AR8327_FWD_CTRL1_MC_FLOOD_S) |
	    (AR8327_PORTS_ALL << AR8327_FWD_CTRL1_BC_FLOOD_S);
	ar8xxx_write(priv, AR8327_REG_FWD_CTRL1, t);

	/* enable jumbo frames */
	ar8xxx_rmw(priv, AR8327_REG_MAX_FRAME_SIZE,
		   AR8327_MAX_FRAME_SIZE_MTU, 9018 + 8 + 2);

	/* Enable MIB counters */
	ar8xxx_reg_set(priv, AR8327_REG_MODULE_EN,
		       AR8327_MODULE_EN_MIB);

	/* Disable EEE on all phy's due to stability issues */
	for (i = 0; i < AR8XXX_NUM_PHYS; i++)
		data->eee[i] = false;
}