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
struct ethsw_port_priv {int /*<<< orphan*/  netdev; } ;
struct TYPE_2__ {int num_ifs; } ;
struct ethsw_core {struct ethsw_port_priv** ports; TYPE_1__ sw_attr; int /*<<< orphan*/  dev; int /*<<< orphan*/  dpsw_handle; int /*<<< orphan*/  mc_io; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int dev_open (int /*<<< orphan*/ ) ; 
 int dpsw_enable (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int ethsw_open(struct ethsw_core *ethsw)
{
	struct ethsw_port_priv *port_priv = NULL;
	int i, err;

	err = dpsw_enable(ethsw->mc_io, 0, ethsw->dpsw_handle);
	if (err) {
		dev_err(ethsw->dev, "dpsw_enable err %d\n", err);
		return err;
	}

	for (i = 0; i < ethsw->sw_attr.num_ifs; i++) {
		port_priv = ethsw->ports[i];
		err = dev_open(port_priv->netdev);
		if (err) {
			netdev_err(port_priv->netdev, "dev_open err %d\n", err);
			return err;
		}
	}

	return 0;
}