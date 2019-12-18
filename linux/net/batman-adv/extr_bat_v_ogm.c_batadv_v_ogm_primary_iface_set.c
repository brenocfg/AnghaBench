#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  ogm_buff_mutex; scalar_t__ ogm_buff; } ;
struct batadv_priv {TYPE_2__ bat_v; } ;
struct batadv_ogm2_packet {int /*<<< orphan*/  orig; } ;
struct batadv_hard_iface {TYPE_1__* net_dev; int /*<<< orphan*/  soft_iface; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct batadv_priv* netdev_priv (int /*<<< orphan*/ ) ; 

void batadv_v_ogm_primary_iface_set(struct batadv_hard_iface *primary_iface)
{
	struct batadv_priv *bat_priv = netdev_priv(primary_iface->soft_iface);
	struct batadv_ogm2_packet *ogm_packet;

	mutex_lock(&bat_priv->bat_v.ogm_buff_mutex);
	if (!bat_priv->bat_v.ogm_buff)
		goto unlock;

	ogm_packet = (struct batadv_ogm2_packet *)bat_priv->bat_v.ogm_buff;
	ether_addr_copy(ogm_packet->orig, primary_iface->net_dev->dev_addr);

unlock:
	mutex_unlock(&bat_priv->bat_v.ogm_buff_mutex);
}