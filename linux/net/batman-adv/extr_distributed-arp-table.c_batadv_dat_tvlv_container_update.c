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
struct batadv_priv {int /*<<< orphan*/  distributed_arp_table; } ;

/* Variables and functions */
 int /*<<< orphan*/  BATADV_TVLV_DAT ; 
 char atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  batadv_tvlv_container_register (struct batadv_priv*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  batadv_tvlv_container_unregister (struct batadv_priv*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void batadv_dat_tvlv_container_update(struct batadv_priv *bat_priv)
{
	char dat_mode;

	dat_mode = atomic_read(&bat_priv->distributed_arp_table);

	switch (dat_mode) {
	case 0:
		batadv_tvlv_container_unregister(bat_priv, BATADV_TVLV_DAT, 1);
		break;
	case 1:
		batadv_tvlv_container_register(bat_priv, BATADV_TVLV_DAT, 1,
					       NULL, 0);
		break;
	}
}