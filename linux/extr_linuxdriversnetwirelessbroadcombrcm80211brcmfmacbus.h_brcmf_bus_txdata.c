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
struct brcmf_bus {int /*<<< orphan*/  dev; TYPE_1__* ops; } ;
struct TYPE_2__ {int (* txdata ) (int /*<<< orphan*/ ,struct sk_buff*) ;} ;

/* Variables and functions */
 int stub1 (int /*<<< orphan*/ ,struct sk_buff*) ; 

__attribute__((used)) static inline int brcmf_bus_txdata(struct brcmf_bus *bus, struct sk_buff *skb)
{
	return bus->ops->txdata(bus->dev, skb);
}