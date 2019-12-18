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
typedef  int u8 ;
struct batadv_priv {int /*<<< orphan*/  hop_penalty; } ;

/* Variables and functions */
 int BATADV_TQ_MAX_VALUE ; 
 int atomic_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static u8 batadv_hop_penalty(u8 tq, const struct batadv_priv *bat_priv)
{
	int hop_penalty = atomic_read(&bat_priv->hop_penalty);
	int new_tq;

	new_tq = tq * (BATADV_TQ_MAX_VALUE - hop_penalty);
	new_tq /= BATADV_TQ_MAX_VALUE;

	return new_tq;
}