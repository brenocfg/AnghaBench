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
struct ieee802154_local {int /*<<< orphan*/  hw; TYPE_1__* ops; } ;
struct TYPE_2__ {int (* xmit_async ) (int /*<<< orphan*/ *,struct sk_buff*) ;} ;

/* Variables and functions */
 int stub1 (int /*<<< orphan*/ *,struct sk_buff*) ; 

__attribute__((used)) static inline int
drv_xmit_async(struct ieee802154_local *local, struct sk_buff *skb)
{
	return local->ops->xmit_async(&local->hw, skb);
}