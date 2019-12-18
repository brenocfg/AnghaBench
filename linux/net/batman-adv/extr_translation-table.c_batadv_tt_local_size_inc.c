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
 int /*<<< orphan*/  batadv_tt_local_size_mod (struct batadv_priv*,unsigned short,int) ; 

__attribute__((used)) static void batadv_tt_local_size_inc(struct batadv_priv *bat_priv,
				     unsigned short vid)
{
	batadv_tt_local_size_mod(bat_priv, vid, 1);
}