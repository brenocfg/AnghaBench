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
struct sock {int dummy; } ;
struct sk_buff {int dummy; } ;
struct scatterlist {int dummy; } ;

/* Variables and functions */
 int decrypt_internal (struct sock*,struct sk_buff*,int /*<<< orphan*/ *,struct scatterlist*,int*,int*,int) ; 

int decrypt_skb(struct sock *sk, struct sk_buff *skb,
		struct scatterlist *sgout)
{
	bool zc = true;
	int chunk;

	return decrypt_internal(sk, skb, NULL, sgout, &chunk, &zc, false);
}