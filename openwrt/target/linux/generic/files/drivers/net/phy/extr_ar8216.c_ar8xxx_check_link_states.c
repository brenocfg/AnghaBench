#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_5__ {int ports; } ;
struct ar8xxx_priv {int* link_up; int /*<<< orphan*/  reg_mutex; TYPE_4__* phy; TYPE_2__* chip; TYPE_1__ dev; } ;
struct TYPE_7__ {int /*<<< orphan*/  dev; } ;
struct TYPE_8__ {TYPE_3__ mdio; } ;
struct TYPE_6__ {int (* read_port_status ) (struct ar8xxx_priv*,int) ;int /*<<< orphan*/  (* atu_flush_port ) (struct ar8xxx_priv*,int) ;} ;

/* Variables and functions */
 int AR8216_PORT_STATUS_LINK_UP ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int,char*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int stub1 (struct ar8xxx_priv*,int) ; 
 int /*<<< orphan*/  stub2 (struct ar8xxx_priv*,int) ; 

__attribute__((used)) static bool
ar8xxx_check_link_states(struct ar8xxx_priv *priv)
{
	bool link_new, changed = false;
	u32 status;
	int i;

	mutex_lock(&priv->reg_mutex);

	for (i = 0; i < priv->dev.ports; i++) {
		status = priv->chip->read_port_status(priv, i);
		link_new = !!(status & AR8216_PORT_STATUS_LINK_UP);
		if (link_new == priv->link_up[i])
			continue;

		priv->link_up[i] = link_new;
		changed = true;
		/* flush ARL entries for this port if it went down*/
		if (!link_new)
			priv->chip->atu_flush_port(priv, i);
		dev_info(&priv->phy->mdio.dev, "Port %d is %s\n",
			 i, link_new ? "up" : "down");
	}

	mutex_unlock(&priv->reg_mutex);

	return changed;
}