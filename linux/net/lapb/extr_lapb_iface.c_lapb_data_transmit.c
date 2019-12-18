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
struct lapb_cb {int /*<<< orphan*/  dev; TYPE_1__* callbacks; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* data_transmit ) (int /*<<< orphan*/ ,struct sk_buff*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,struct sk_buff*) ; 

int lapb_data_transmit(struct lapb_cb *lapb, struct sk_buff *skb)
{
	int used = 0;

	if (lapb->callbacks->data_transmit) {
		lapb->callbacks->data_transmit(lapb->dev, skb);
		used = 1;
	}

	return used;
}