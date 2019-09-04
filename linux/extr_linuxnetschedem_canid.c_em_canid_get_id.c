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
struct sk_buff {scalar_t__ data; } ;
struct can_frame {int /*<<< orphan*/  can_id; } ;
typedef  int /*<<< orphan*/  canid_t ;

/* Variables and functions */

__attribute__((used)) static canid_t em_canid_get_id(struct sk_buff *skb)
{
	/* CAN ID is stored within the data field */
	struct can_frame *cf = (struct can_frame *)skb->data;

	return cf->can_id;
}