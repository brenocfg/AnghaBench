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
struct ath_vif {int dummy; } ;
struct ath_softc {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline void ath9k_beacon_add_noa(struct ath_softc *sc, struct ath_vif *avp,
					struct sk_buff *skb)
{
}