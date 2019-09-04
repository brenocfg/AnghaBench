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
struct sk_buff {int /*<<< orphan*/  len; TYPE_1__* dev; } ;
struct TYPE_2__ {int type; } ;

/* Variables and functions */
#define  ARPHRD_ETHER 129 
#define  ARPHRD_LOOPBACK 128 
 int EINVAL ; 
 int /*<<< orphan*/  ETH_P_802_2 ; 
 int dev_hard_header (struct sk_buff*,TYPE_1__*,int /*<<< orphan*/ ,unsigned char const*,unsigned char const*,int /*<<< orphan*/ ) ; 

int llc_mac_hdr_init(struct sk_buff *skb,
		     const unsigned char *sa, const unsigned char *da)
{
	int rc = -EINVAL;

	switch (skb->dev->type) {
	case ARPHRD_ETHER:
	case ARPHRD_LOOPBACK:
		rc = dev_hard_header(skb, skb->dev, ETH_P_802_2, da, sa,
				     skb->len);
		if (rc > 0)
			rc = 0;
		break;
	default:
		break;
	}
	return rc;
}