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
typedef  int u32 ;
struct sock {int dummy; } ;
struct TYPE_2__ {scalar_t__ start; int size; scalar_t__ end; } ;
struct sk_msg {TYPE_1__ sg; } ;
struct scatterlist {int length; int offset; } ;
struct page {int dummy; } ;

/* Variables and functions */
 int MSG_SENDPAGE_NOPOLICY ; 
 int do_tcp_sendpages (struct sock*,struct page*,int,int,int) ; 
 int kernel_sendpage_locked (struct sock*,struct page*,int,int,int) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 
 int /*<<< orphan*/  sg_init_table (struct scatterlist*,int) ; 
 struct page* sg_page (struct scatterlist*) ; 
 int /*<<< orphan*/  sk_mem_uncharge (struct sock*,int) ; 
 struct scatterlist* sk_msg_elem (struct sk_msg*,scalar_t__) ; 
 int /*<<< orphan*/  sk_msg_iter_next (struct sk_msg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  start ; 
 int /*<<< orphan*/  tcp_rate_check_app_limited (struct sock*) ; 
 int tls_sw_has_ctx_tx (struct sock*) ; 

__attribute__((used)) static int tcp_bpf_push(struct sock *sk, struct sk_msg *msg, u32 apply_bytes,
			int flags, bool uncharge)
{
	bool apply = apply_bytes;
	struct scatterlist *sge;
	struct page *page;
	int size, ret = 0;
	u32 off;

	while (1) {
		bool has_tx_ulp;

		sge = sk_msg_elem(msg, msg->sg.start);
		size = (apply && apply_bytes < sge->length) ?
			apply_bytes : sge->length;
		off  = sge->offset;
		page = sg_page(sge);

		tcp_rate_check_app_limited(sk);
retry:
		has_tx_ulp = tls_sw_has_ctx_tx(sk);
		if (has_tx_ulp) {
			flags |= MSG_SENDPAGE_NOPOLICY;
			ret = kernel_sendpage_locked(sk,
						     page, off, size, flags);
		} else {
			ret = do_tcp_sendpages(sk, page, off, size, flags);
		}

		if (ret <= 0)
			return ret;
		if (apply)
			apply_bytes -= ret;
		msg->sg.size -= ret;
		sge->offset += ret;
		sge->length -= ret;
		if (uncharge)
			sk_mem_uncharge(sk, ret);
		if (ret != size) {
			size -= ret;
			off  += ret;
			goto retry;
		}
		if (!sge->length) {
			put_page(page);
			sk_msg_iter_next(msg, start);
			sg_init_table(sge, 1);
			if (msg->sg.start == msg->sg.end)
				break;
		}
		if (apply && !apply_bytes)
			break;
	}

	return 0;
}