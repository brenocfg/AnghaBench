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
struct batadv_priv {struct batadv_algo_ops* algo_ops; } ;
struct batadv_algo_ops {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 struct batadv_algo_ops* batadv_algo_get (char*) ; 

int batadv_algo_select(struct batadv_priv *bat_priv, char *name)
{
	struct batadv_algo_ops *bat_algo_ops;

	bat_algo_ops = batadv_algo_get(name);
	if (!bat_algo_ops)
		return -EINVAL;

	bat_priv->algo_ops = bat_algo_ops;

	return 0;
}