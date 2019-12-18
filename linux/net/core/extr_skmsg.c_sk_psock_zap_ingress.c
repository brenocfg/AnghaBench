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
struct sk_psock {int /*<<< orphan*/  ingress_skb; } ;

/* Variables and functions */
 int /*<<< orphan*/  __sk_psock_purge_ingress_msg (struct sk_psock*) ; 
 int /*<<< orphan*/  __skb_queue_purge (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void sk_psock_zap_ingress(struct sk_psock *psock)
{
	__skb_queue_purge(&psock->ingress_skb);
	__sk_psock_purge_ingress_msg(psock);
}