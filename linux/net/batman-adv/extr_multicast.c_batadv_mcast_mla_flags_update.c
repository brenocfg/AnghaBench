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
struct batadv_tvlv_mcast_data {int /*<<< orphan*/  reserved; int /*<<< orphan*/  flags; } ;
struct batadv_mcast_mla_flags {int /*<<< orphan*/  tvlv_flags; } ;
struct TYPE_2__ {struct batadv_mcast_mla_flags mla_flags; } ;
struct batadv_priv {TYPE_1__ mcast; } ;
typedef  int /*<<< orphan*/  mcast_data ;

/* Variables and functions */
 int /*<<< orphan*/  BATADV_TVLV_MCAST ; 
 int /*<<< orphan*/  batadv_mcast_bridge_log (struct batadv_priv*,struct batadv_mcast_mla_flags*) ; 
 int /*<<< orphan*/  batadv_mcast_flags_log (struct batadv_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  batadv_tvlv_container_register (struct batadv_priv*,int /*<<< orphan*/ ,int,struct batadv_tvlv_mcast_data*,int) ; 
 int /*<<< orphan*/  memcmp (struct batadv_mcast_mla_flags*,struct batadv_mcast_mla_flags*,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
batadv_mcast_mla_flags_update(struct batadv_priv *bat_priv,
			      struct batadv_mcast_mla_flags *flags)
{
	struct batadv_tvlv_mcast_data mcast_data;

	if (!memcmp(flags, &bat_priv->mcast.mla_flags, sizeof(*flags)))
		return;

	batadv_mcast_bridge_log(bat_priv, flags);
	batadv_mcast_flags_log(bat_priv, flags->tvlv_flags);

	mcast_data.flags = flags->tvlv_flags;
	memset(mcast_data.reserved, 0, sizeof(mcast_data.reserved));

	batadv_tvlv_container_register(bat_priv, BATADV_TVLV_MCAST, 2,
				       &mcast_data, sizeof(mcast_data));

	bat_priv->mcast.mla_flags = *flags;
}