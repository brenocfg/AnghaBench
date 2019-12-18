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
struct hsr_priv {int dummy; } ;
struct hsr_port {int /*<<< orphan*/  dev; int /*<<< orphan*/  port_list; struct hsr_priv* hsr; } ;

/* Variables and functions */
 int /*<<< orphan*/  HSR_PT_MASTER ; 
 int /*<<< orphan*/  dev_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_set_mtu (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_set_promiscuity (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  hsr_get_max_mtu (struct hsr_priv*) ; 
 struct hsr_port* hsr_port_get_hsr (struct hsr_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct hsr_port*) ; 
 int /*<<< orphan*/  list_del_rcu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netdev_rx_handler_unregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_update_features (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  synchronize_rcu () ; 

void hsr_del_port(struct hsr_port *port)
{
	struct hsr_priv *hsr;
	struct hsr_port *master;

	hsr = port->hsr;
	master = hsr_port_get_hsr(hsr, HSR_PT_MASTER);
	list_del_rcu(&port->port_list);

	if (port != master) {
		if (master) {
			netdev_update_features(master->dev);
			dev_set_mtu(master->dev, hsr_get_max_mtu(hsr));
		}
		netdev_rx_handler_unregister(port->dev);
		dev_set_promiscuity(port->dev, -1);
	}

	/* FIXME?
	 * netdev_upper_dev_unlink(port->dev, port->hsr->dev);
	 */

	synchronize_rcu();

	if (port != master)
		dev_put(port->dev);
	kfree(port);
}