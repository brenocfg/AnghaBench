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
struct usbnet {TYPE_1__* udev; } ;
struct sk_buff {int len; int* data; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  skb_trim (struct sk_buff*,int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int ch9200_rx_fixup(struct usbnet *dev, struct sk_buff *skb)
{
	int len = 0;
	int rx_overhead = 0;

	rx_overhead = 64;

	if (unlikely(skb->len < rx_overhead)) {
		dev_err(&dev->udev->dev, "unexpected tiny rx frame\n");
		return 0;
	}

	len = (skb->data[skb->len - 16] | skb->data[skb->len - 15] << 8);
	skb_trim(skb, len);

	return 1;
}