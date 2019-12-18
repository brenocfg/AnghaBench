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
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u16 ;
struct sk_buff {int dummy; } ;
struct nfc_llcp_sock {int /*<<< orphan*/  ssap; int /*<<< orphan*/  dsap; int /*<<< orphan*/  sk; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ LLCP_HEADER_SIZE ; 
 int /*<<< orphan*/  MSG_DONTWAIT ; 
 struct sk_buff* llcp_add_header (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sk_buff* nfc_alloc_send_skb (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static struct sk_buff *llcp_allocate_pdu(struct nfc_llcp_sock *sock,
					 u8 cmd, u16 size)
{
	struct sk_buff *skb;
	int err;

	if (sock->ssap == 0)
		return NULL;

	skb = nfc_alloc_send_skb(sock->dev, &sock->sk, MSG_DONTWAIT,
				 size + LLCP_HEADER_SIZE, &err);
	if (skb == NULL) {
		pr_err("Could not allocate PDU\n");
		return NULL;
	}

	skb = llcp_add_header(skb, sock->dsap, sock->ssap, cmd);

	return skb;
}