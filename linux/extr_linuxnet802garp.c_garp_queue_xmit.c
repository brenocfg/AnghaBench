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
struct sk_buff {int dummy; } ;
struct garp_applicant {int /*<<< orphan*/  queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_queue_xmit (struct sk_buff*) ; 
 struct sk_buff* skb_dequeue (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void garp_queue_xmit(struct garp_applicant *app)
{
	struct sk_buff *skb;

	while ((skb = skb_dequeue(&app->queue)))
		dev_queue_xmit(skb);
}