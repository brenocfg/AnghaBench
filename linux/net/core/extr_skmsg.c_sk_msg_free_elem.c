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
typedef  int u32 ;
struct sock {int dummy; } ;
struct sk_msg {int /*<<< orphan*/  skb; } ;
struct scatterlist {int length; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct scatterlist*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  put_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sg_page (struct scatterlist*) ; 
 int /*<<< orphan*/  sk_mem_uncharge (struct sock*,int) ; 
 struct scatterlist* sk_msg_elem (struct sk_msg*,int) ; 

__attribute__((used)) static int sk_msg_free_elem(struct sock *sk, struct sk_msg *msg, u32 i,
			    bool charge)
{
	struct scatterlist *sge = sk_msg_elem(msg, i);
	u32 len = sge->length;

	if (charge)
		sk_mem_uncharge(sk, len);
	if (!msg->skb)
		put_page(sg_page(sge));
	memset(sge, 0, sizeof(*sge));
	return len;
}