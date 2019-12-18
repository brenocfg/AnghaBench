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
struct tls_record_info {int num_frags; int /*<<< orphan*/ * frags; int /*<<< orphan*/  list; scalar_t__ len; scalar_t__ end_seq; } ;
struct tls_prot_info {int dummy; } ;
struct tls_offload_context_tx {int /*<<< orphan*/ * sg_tx_data; int /*<<< orphan*/ * open_record; int /*<<< orphan*/  records_list; } ;
struct tls_context {int /*<<< orphan*/  tx; int /*<<< orphan*/  flags; struct tls_prot_info prot_info; } ;
struct tcp_sock {scalar_t__ write_seq; } ;
struct sock {int dummy; } ;
typedef  int /*<<< orphan*/  skb_frag_t ;

/* Variables and functions */
 int /*<<< orphan*/  TLS_TX_SYNC_SCHED ; 
 int /*<<< orphan*/  get_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sg_mark_end (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sg_set_page (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sg_unmark_end (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sk_mem_charge (struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_frag_off (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_frag_page (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_frag_size (int /*<<< orphan*/ *) ; 
 struct tcp_sock* tcp_sk (struct sock*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tls_advance_record_sn (struct sock*,struct tls_prot_info*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tls_device_resync_tx (struct sock*,struct tls_context*,scalar_t__) ; 
 int tls_push_sg (struct sock*,struct tls_context*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int tls_push_record(struct sock *sk,
			   struct tls_context *ctx,
			   struct tls_offload_context_tx *offload_ctx,
			   struct tls_record_info *record,
			   int flags)
{
	struct tls_prot_info *prot = &ctx->prot_info;
	struct tcp_sock *tp = tcp_sk(sk);
	skb_frag_t *frag;
	int i;

	record->end_seq = tp->write_seq + record->len;
	list_add_tail_rcu(&record->list, &offload_ctx->records_list);
	offload_ctx->open_record = NULL;

	if (test_bit(TLS_TX_SYNC_SCHED, &ctx->flags))
		tls_device_resync_tx(sk, ctx, tp->write_seq);

	tls_advance_record_sn(sk, prot, &ctx->tx);

	for (i = 0; i < record->num_frags; i++) {
		frag = &record->frags[i];
		sg_unmark_end(&offload_ctx->sg_tx_data[i]);
		sg_set_page(&offload_ctx->sg_tx_data[i], skb_frag_page(frag),
			    skb_frag_size(frag), skb_frag_off(frag));
		sk_mem_charge(sk, skb_frag_size(frag));
		get_page(skb_frag_page(frag));
	}
	sg_mark_end(&offload_ctx->sg_tx_data[record->num_frags - 1]);

	/* all ready, send */
	return tls_push_sg(sk, ctx, offload_ctx->sg_tx_data, 0, flags);
}