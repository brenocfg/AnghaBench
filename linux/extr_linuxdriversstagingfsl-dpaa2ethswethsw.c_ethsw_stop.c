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
struct ethsw_core {int /*<<< orphan*/  dev; int /*<<< orphan*/  dpsw_handle; int /*<<< orphan*/  mc_io; struct ethsw_port_priv** ports; TYPE_1__ sw_attr; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int dpsw_disable (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ethsw_stop(struct ethsw_core *ethsw)
{
	struct ethsw_port_priv *port_priv = NULL;
	int i, err;

	for (i = 0; i < ethsw->sw_attr.num_ifs; i++) {
		port_priv = ethsw->ports[i];
		dev_close(port_priv->netdev);
	}

	err = dpsw_disable(ethsw->mc_io, 0, ethsw->dpsw_handle);
	if (err) {
		dev_err(ethsw->dev, "dpsw_disable err %d\n", err);
		return err;
	}

	return 0;
}