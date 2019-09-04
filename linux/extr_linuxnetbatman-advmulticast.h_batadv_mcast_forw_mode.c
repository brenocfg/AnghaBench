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
struct sk_buff {int dummy; } ;
struct batadv_priv {int dummy; } ;
struct batadv_orig_node {int dummy; } ;
typedef  enum batadv_forw_mode { ____Placeholder_batadv_forw_mode } batadv_forw_mode ;

/* Variables and functions */
 int BATADV_FORW_ALL ; 

__attribute__((used)) static inline enum batadv_forw_mode
batadv_mcast_forw_mode(struct batadv_priv *bat_priv, struct sk_buff *skb,
		       struct batadv_orig_node **mcast_single_orig)
{
	return BATADV_FORW_ALL;
}