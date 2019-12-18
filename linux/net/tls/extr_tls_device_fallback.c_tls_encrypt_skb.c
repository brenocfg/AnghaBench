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
 struct sk_buff* tls_sw_fallback (int /*<<< orphan*/ ,struct sk_buff*) ; 

struct sk_buff *tls_encrypt_skb(struct sk_buff *skb)
{
	return tls_sw_fallback(skb->sk, skb);
}