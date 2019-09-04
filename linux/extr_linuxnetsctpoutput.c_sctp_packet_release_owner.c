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
struct sk_buff {int /*<<< orphan*/  sk; } ;

/* Variables and functions */
 int /*<<< orphan*/  sk_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sctp_packet_release_owner(struct sk_buff *skb)
{
	sk_free(skb->sk);
}