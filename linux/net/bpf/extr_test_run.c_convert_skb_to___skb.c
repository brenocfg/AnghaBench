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
struct sk_buff {int /*<<< orphan*/  priority; scalar_t__ cb; } ;
struct qdisc_skb_cb {int /*<<< orphan*/  data; } ;
struct __sk_buff {int /*<<< orphan*/  cb; int /*<<< orphan*/  priority; } ;

/* Variables and functions */
 int /*<<< orphan*/  QDISC_CB_PRIV_LEN ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void convert_skb_to___skb(struct sk_buff *skb, struct __sk_buff *__skb)
{
	struct qdisc_skb_cb *cb = (struct qdisc_skb_cb *)skb->cb;

	if (!__skb)
		return;

	__skb->priority = skb->priority;
	memcpy(__skb->cb, &cb->data, QDISC_CB_PRIV_LEN);
}