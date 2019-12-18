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
struct sock {int dummy; } ;
struct sk_buff {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  __hci_send_to_channel (unsigned short,struct sk_buff*,int,struct sock*) ; 
 TYPE_1__ hci_sk_list ; 
 int /*<<< orphan*/  read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock (int /*<<< orphan*/ *) ; 

void hci_send_to_channel(unsigned short channel, struct sk_buff *skb,
			 int flag, struct sock *skip_sk)
{
	read_lock(&hci_sk_list.lock);
	__hci_send_to_channel(channel, skb, flag, skip_sk);
	read_unlock(&hci_sk_list.lock);
}