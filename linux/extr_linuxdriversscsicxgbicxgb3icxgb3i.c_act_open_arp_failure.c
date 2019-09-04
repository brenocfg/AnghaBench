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
struct t3cdev {int dummy; } ;
struct sk_buff {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cxgbi_sock_act_open_req_arp_failure (int /*<<< orphan*/ *,struct sk_buff*) ; 

__attribute__((used)) static inline void act_open_arp_failure(struct t3cdev *dev, struct sk_buff *skb)
{
	cxgbi_sock_act_open_req_arp_failure(NULL, skb);
}