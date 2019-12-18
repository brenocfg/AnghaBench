#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct sk_buff {int dummy; } ;
struct TYPE_6__ {scalar_t__ shadowing; scalar_t__ exists; } ;
struct TYPE_5__ {scalar_t__ shadowing; scalar_t__ exists; } ;
struct TYPE_8__ {TYPE_2__ querier_ipv6; TYPE_1__ querier_ipv4; scalar_t__ bridged; int /*<<< orphan*/  tvlv_flags; } ;
struct TYPE_7__ {TYPE_4__ mla_flags; } ;
struct batadv_priv {TYPE_3__ mcast; } ;

/* Variables and functions */
 int /*<<< orphan*/  BATADV_ATTR_MCAST_FLAGS ; 
 int /*<<< orphan*/  BATADV_ATTR_MCAST_FLAGS_PRIV ; 
 int /*<<< orphan*/  BATADV_MCAST_FLAGS_BRIDGED ; 
 int /*<<< orphan*/  BATADV_MCAST_FLAGS_QUERIER_IPV4_EXISTS ; 
 int /*<<< orphan*/  BATADV_MCAST_FLAGS_QUERIER_IPV4_SHADOWING ; 
 int /*<<< orphan*/  BATADV_MCAST_FLAGS_QUERIER_IPV6_EXISTS ; 
 int /*<<< orphan*/  BATADV_MCAST_FLAGS_QUERIER_IPV6_SHADOWING ; 
 int /*<<< orphan*/  BATADV_NO_FLAGS ; 
 int EMSGSIZE ; 
 scalar_t__ nla_put_u32 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int batadv_mcast_mesh_info_put(struct sk_buff *msg,
			       struct batadv_priv *bat_priv)
{
	u32 flags = bat_priv->mcast.mla_flags.tvlv_flags;
	u32 flags_priv = BATADV_NO_FLAGS;

	if (bat_priv->mcast.mla_flags.bridged) {
		flags_priv |= BATADV_MCAST_FLAGS_BRIDGED;

		if (bat_priv->mcast.mla_flags.querier_ipv4.exists)
			flags_priv |= BATADV_MCAST_FLAGS_QUERIER_IPV4_EXISTS;
		if (bat_priv->mcast.mla_flags.querier_ipv6.exists)
			flags_priv |= BATADV_MCAST_FLAGS_QUERIER_IPV6_EXISTS;
		if (bat_priv->mcast.mla_flags.querier_ipv4.shadowing)
			flags_priv |= BATADV_MCAST_FLAGS_QUERIER_IPV4_SHADOWING;
		if (bat_priv->mcast.mla_flags.querier_ipv6.shadowing)
			flags_priv |= BATADV_MCAST_FLAGS_QUERIER_IPV6_SHADOWING;
	}

	if (nla_put_u32(msg, BATADV_ATTR_MCAST_FLAGS, flags) ||
	    nla_put_u32(msg, BATADV_ATTR_MCAST_FLAGS_PRIV, flags_priv))
		return -EMSGSIZE;

	return 0;
}