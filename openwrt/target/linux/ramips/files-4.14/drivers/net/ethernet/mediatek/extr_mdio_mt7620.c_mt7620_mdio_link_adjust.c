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
struct fe_priv {TYPE_1__* phy; int /*<<< orphan*/ * link; } ;
struct TYPE_2__ {scalar_t__* duplex; int /*<<< orphan*/ * speed; } ;

/* Variables and functions */
 scalar_t__ DUPLEX_FULL ; 
 int /*<<< orphan*/  mt7620_handle_carrier (struct fe_priv*) ; 
 int /*<<< orphan*/  mt7620_print_link_state (struct fe_priv*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void mt7620_mdio_link_adjust(struct fe_priv *priv, int port)
{
	mt7620_print_link_state(priv, port, priv->link[port],
				priv->phy->speed[port],
				(priv->phy->duplex[port] == DUPLEX_FULL));
	mt7620_handle_carrier(priv);
}