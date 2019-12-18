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
typedef  int u32 ;
struct batadv_priv {int /*<<< orphan*/  hop_penalty; } ;
struct TYPE_2__ {int flags; } ;
struct batadv_hard_iface {TYPE_1__ bat_v; } ;

/* Variables and functions */
 int BATADV_FULL_DUPLEX ; 
 struct batadv_hard_iface* BATADV_IF_DEFAULT ; 
 int BATADV_TQ_MAX_VALUE ; 
 int atomic_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static u32 batadv_v_forward_penalty(struct batadv_priv *bat_priv,
				    struct batadv_hard_iface *if_incoming,
				    struct batadv_hard_iface *if_outgoing,
				    u32 throughput)
{
	int hop_penalty = atomic_read(&bat_priv->hop_penalty);
	int hop_penalty_max = BATADV_TQ_MAX_VALUE;

	/* Don't apply hop penalty in default originator table. */
	if (if_outgoing == BATADV_IF_DEFAULT)
		return throughput;

	/* Forwarding on the same WiFi interface cuts the throughput in half
	 * due to the store & forward characteristics of WIFI.
	 * Very low throughput values are the exception.
	 */
	if (throughput > 10 &&
	    if_incoming == if_outgoing &&
	    !(if_incoming->bat_v.flags & BATADV_FULL_DUPLEX))
		return throughput / 2;

	/* hop penalty of 255 equals 100% */
	return throughput * (hop_penalty_max - hop_penalty) / hop_penalty_max;
}