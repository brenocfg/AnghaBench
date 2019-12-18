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
typedef  void* u8 ;
struct sock {int dummy; } ;
struct sk_buff {int dummy; } ;
struct pnpipehdr {void* error_code; int /*<<< orphan*/  pipe_handle; void* message_id; void* utid; } ;
struct pep_sock {int /*<<< orphan*/  pipe_handle; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct sk_buff* pep_alloc_skb (struct sock*,void const*,int,int /*<<< orphan*/ ) ; 
 struct pep_sock* pep_sk (struct sock*) ; 
 int pn_skb_send (struct sock*,struct sk_buff*,int /*<<< orphan*/ *) ; 
 struct pnpipehdr* pnp_hdr (struct sk_buff*) ; 

__attribute__((used)) static int pipe_handler_request(struct sock *sk, u8 id, u8 code,
				const void *data, int len)
{
	struct pep_sock *pn = pep_sk(sk);
	struct pnpipehdr *ph;
	struct sk_buff *skb;

	skb = pep_alloc_skb(sk, data, len, GFP_KERNEL);
	if (!skb)
		return -ENOMEM;

	ph = pnp_hdr(skb);
	ph->utid = id; /* whatever */
	ph->message_id = id;
	ph->pipe_handle = pn->pipe_handle;
	ph->error_code = code;
	return pn_skb_send(sk, skb, NULL);
}