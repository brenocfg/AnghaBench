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
struct batadv_priv {int dummy; } ;

/* Variables and functions */
 int batadv_v_ogm_init (struct batadv_priv*) ; 

int batadv_v_mesh_init(struct batadv_priv *bat_priv)
{
	int ret = 0;

	ret = batadv_v_ogm_init(bat_priv);
	if (ret < 0)
		return ret;

	return 0;
}