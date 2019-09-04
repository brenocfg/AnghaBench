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
struct sas_port {int /*<<< orphan*/  phy_list_mutex; int /*<<< orphan*/  num_phys; } ;
struct sas_phy {int /*<<< orphan*/  port_siblings; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sas_port_delete_link (struct sas_port*,struct sas_phy*) ; 

void sas_port_delete_phy(struct sas_port *port, struct sas_phy *phy)
{
	mutex_lock(&port->phy_list_mutex);
	sas_port_delete_link(port, phy);
	list_del_init(&phy->port_siblings);
	port->num_phys--;
	mutex_unlock(&port->phy_list_mutex);
}