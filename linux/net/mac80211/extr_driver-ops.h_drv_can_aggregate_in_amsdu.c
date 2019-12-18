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
struct ieee80211_local {int /*<<< orphan*/  hw; TYPE_1__* ops; } ;
struct TYPE_2__ {int (* can_aggregate_in_amsdu ) (int /*<<< orphan*/ *,struct sk_buff*,struct sk_buff*) ;} ;

/* Variables and functions */
 int stub1 (int /*<<< orphan*/ *,struct sk_buff*,struct sk_buff*) ; 

__attribute__((used)) static inline int drv_can_aggregate_in_amsdu(struct ieee80211_local *local,
					     struct sk_buff *head,
					     struct sk_buff *skb)
{
	if (!local->ops->can_aggregate_in_amsdu)
		return true;

	return local->ops->can_aggregate_in_amsdu(&local->hw, head, skb);
}