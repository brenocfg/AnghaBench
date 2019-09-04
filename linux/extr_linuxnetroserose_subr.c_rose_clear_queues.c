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
struct sock {int /*<<< orphan*/  sk_write_queue; } ;
struct TYPE_2__ {int /*<<< orphan*/  ack_queue; } ;

/* Variables and functions */
 TYPE_1__* rose_sk (struct sock*) ; 
 int /*<<< orphan*/  skb_queue_purge (int /*<<< orphan*/ *) ; 

void rose_clear_queues(struct sock *sk)
{
	skb_queue_purge(&sk->sk_write_queue);
	skb_queue_purge(&rose_sk(sk)->ack_queue);
}