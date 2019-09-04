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
struct TYPE_2__ {int /*<<< orphan*/ * ht; } ;

/* Variables and functions */
 int RAW_HTABLE_SIZE ; 
 int /*<<< orphan*/  ip_hdr (struct sk_buff*) ; 
 TYPE_1__ raw_v4_hashinfo ; 
 int /*<<< orphan*/  raw_v4_input (struct sk_buff*,int /*<<< orphan*/ ,int) ; 
 struct sock* sk_head (int /*<<< orphan*/ *) ; 

int raw_local_deliver(struct sk_buff *skb, int protocol)
{
	int hash;
	struct sock *raw_sk;

	hash = protocol & (RAW_HTABLE_SIZE - 1);
	raw_sk = sk_head(&raw_v4_hashinfo.ht[hash]);

	/* If there maybe a raw socket we must check - if not we
	 * don't care less
	 */
	if (raw_sk && !raw_v4_input(skb, ip_hdr(skb), hash))
		raw_sk = NULL;

	return raw_sk != NULL;

}