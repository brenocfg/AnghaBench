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
struct tls_offload_context_tx {int /*<<< orphan*/  open_record; } ;
struct sock {TYPE_1__* sk_prot; int /*<<< orphan*/  sk_allocation; } ;
struct page_frag {scalar_t__ size; scalar_t__ offset; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* enter_memory_pressure ) (struct sock*) ;} ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  sk_page_frag_refill (struct sock*,struct page_frag*) ; 
 int /*<<< orphan*/  sk_stream_moderate_sndbuf (struct sock*) ; 
 int /*<<< orphan*/  skb_page_frag_refill (size_t,struct page_frag*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct sock*) ; 
 int tls_create_new_record (struct tls_offload_context_tx*,struct page_frag*,size_t) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int tls_do_allocation(struct sock *sk,
			     struct tls_offload_context_tx *offload_ctx,
			     struct page_frag *pfrag,
			     size_t prepend_size)
{
	int ret;

	if (!offload_ctx->open_record) {
		if (unlikely(!skb_page_frag_refill(prepend_size, pfrag,
						   sk->sk_allocation))) {
			sk->sk_prot->enter_memory_pressure(sk);
			sk_stream_moderate_sndbuf(sk);
			return -ENOMEM;
		}

		ret = tls_create_new_record(offload_ctx, pfrag, prepend_size);
		if (ret)
			return ret;

		if (pfrag->size > pfrag->offset)
			return 0;
	}

	if (!sk_page_frag_refill(sk, pfrag))
		return -ENOMEM;

	return 0;
}