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
struct TYPE_2__ {int /*<<< orphan*/ * hash; } ;
struct batadv_priv {TYPE_1__ dat; } ;

/* Variables and functions */
 int /*<<< orphan*/  __batadv_dat_purge (struct batadv_priv*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  batadv_hash_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void batadv_dat_hash_free(struct batadv_priv *bat_priv)
{
	if (!bat_priv->dat.hash)
		return;

	__batadv_dat_purge(bat_priv, NULL);

	batadv_hash_destroy(bat_priv->dat.hash);

	bat_priv->dat.hash = NULL;
}