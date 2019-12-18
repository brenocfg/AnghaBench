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
struct nfc_llcp_local {int /*<<< orphan*/  rx_work; int /*<<< orphan*/  link_timer; struct sk_buff* rx_pending; } ;

/* Variables and functions */
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __nfc_llcp_recv(struct nfc_llcp_local *local, struct sk_buff *skb)
{
	local->rx_pending = skb;
	del_timer(&local->link_timer);
	schedule_work(&local->rx_work);
}