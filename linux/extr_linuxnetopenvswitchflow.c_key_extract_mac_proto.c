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
struct sk_buff {int /*<<< orphan*/  protocol; TYPE_1__* dev; } ;
struct TYPE_2__ {int type; } ;

/* Variables and functions */
#define  ARPHRD_ETHER 129 
#define  ARPHRD_NONE 128 
 int EINVAL ; 
 int /*<<< orphan*/  ETH_P_TEB ; 
 int MAC_PROTO_ETHERNET ; 
 int MAC_PROTO_NONE ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int key_extract_mac_proto(struct sk_buff *skb)
{
	switch (skb->dev->type) {
	case ARPHRD_ETHER:
		return MAC_PROTO_ETHERNET;
	case ARPHRD_NONE:
		if (skb->protocol == htons(ETH_P_TEB))
			return MAC_PROTO_ETHERNET;
		return MAC_PROTO_NONE;
	}
	WARN_ON_ONCE(1);
	return -EINVAL;
}