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
struct sk_buff {int dummy; } ;
struct ieee80211_tx_control {int dummy; } ;
struct ieee80211_local {int /*<<< orphan*/  hw; TYPE_1__* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* tx ) (int /*<<< orphan*/ *,struct ieee80211_tx_control*,struct sk_buff*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,struct ieee80211_tx_control*,struct sk_buff*) ; 

__attribute__((used)) static inline void drv_tx(struct ieee80211_local *local,
			  struct ieee80211_tx_control *control,
			  struct sk_buff *skb)
{
	local->ops->tx(&local->hw, control, skb);
}