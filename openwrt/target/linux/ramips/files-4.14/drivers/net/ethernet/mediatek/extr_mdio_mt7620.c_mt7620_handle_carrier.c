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
struct fe_priv {int /*<<< orphan*/  netdev; int /*<<< orphan*/  phy; } ;

/* Variables and functions */
 scalar_t__ mt7620_has_carrier (struct fe_priv*) ; 
 int /*<<< orphan*/  netif_carrier_off (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_carrier_on (int /*<<< orphan*/ ) ; 

void mt7620_handle_carrier(struct fe_priv *priv)
{
	if (!priv->phy)
		return;

	if (mt7620_has_carrier(priv))
		netif_carrier_on(priv->netdev);
	else
		netif_carrier_off(priv->netdev);
}