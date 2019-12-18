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
struct net_device {struct can_ml_priv* ml_priv; } ;
struct j1939_priv {int dummy; } ;
struct can_ml_priv {struct j1939_priv* j1939_priv; } ;

/* Variables and functions */

__attribute__((used)) static inline void j1939_priv_set(struct net_device *ndev,
				  struct j1939_priv *priv)
{
	struct can_ml_priv *can_ml_priv = ndev->ml_priv;

	can_ml_priv->j1939_priv = priv;
}