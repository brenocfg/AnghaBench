#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct tls_record_info {int num_frags; TYPE_1__* frags; int /*<<< orphan*/  list; scalar_t__ len; scalar_t__ end_seq; } ;
struct tls_offload_context_tx {int /*<<< orphan*/ * sg_tx_data; int /*<<< orphan*/ * open_record; int /*<<< orphan*/  lock; int /*<<< orphan*/  records_list; } ;
struct TYPE_6__ {int /*<<< orphan*/  tag_size; scalar_t__ prepend_size; } ;
struct tls_context {TYPE_2__ tx; int /*<<< orphan*/  flags; } ;
struct tcp_sock {scalar_t__ write_seq; } ;
struct sock {int dummy; } ;
struct page_frag {scalar_t__ offset; int /*<<< orphan*/  page; } ;
struct TYPE_5__ {int /*<<< orphan*/  size; int /*<<< orphan*/  page_offset; } ;
typedef  TYPE_1__ skb_frag_t ;

/* Variables and functions */
 int /*<<< orphan*/  TLS_PENDING_CLOSED_RECORD ; 
 int /*<<< orphan*/  get_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sg_mark_end (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sg_set_page (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sg_unmark_end (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sk_mem_charge (struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_frag_address (TYPE_1__*) ; 
 int /*<<< orphan*/  skb_frag_page (TYPE_1__*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 struct tcp_sock* tcp_sk (struct sock*) ; 
 int /*<<< orphan*/  tls_advance_record_sn (struct sock*,TYPE_2__*) ; 
 int /*<<< orphan*/  tls_append_frag (struct tls_record_info*,struct page_frag*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tls_fill_prepend (struct tls_context*,int /*<<< orphan*/ ,scalar_t__,unsigned char) ; 
 int tls_push_sg (struct sock*,struct tls_context*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int tls_push_record(struct sock *sk,
			   struct tls_context *ctx,
			   struct tls_offload_context_tx *offload_ctx,
			   struct tls_record_info *record,
			   struct page_frag *pfrag,
			   int flags,
			   unsigned char record_type)
{
	struct tcp_sock *tp = tcp_sk(sk);
	struct page_frag dummy_tag_frag;
	skb_frag_t *frag;
	int i;

	/* fill prepend */
	frag = &record->frags[0];
	tls_fill_prepend(ctx,
			 skb_frag_address(frag),
			 record->len - ctx->tx.prepend_size,
			 record_type);

	/* HW doesn't care about the data in the tag, because it fills it. */
	dummy_tag_frag.page = skb_frag_page(frag);
	dummy_tag_frag.offset = 0;

	tls_append_frag(record, &dummy_tag_frag, ctx->tx.tag_size);
	record->end_seq = tp->write_seq + record->len;
	spin_lock_irq(&offload_ctx->lock);
	list_add_tail(&record->list, &offload_ctx->records_list);
	spin_unlock_irq(&offload_ctx->lock);
	offload_ctx->open_record = NULL;
	set_bit(TLS_PENDING_CLOSED_RECORD, &ctx->flags);
	tls_advance_record_sn(sk, &ctx->tx);

	for (i = 0; i < record->num_frags; i++) {
		frag = &record->frags[i];
		sg_unmark_end(&offload_ctx->sg_tx_data[i]);
		sg_set_page(&offload_ctx->sg_tx_data[i], skb_frag_page(frag),
			    frag->size, frag->page_offset);
		sk_mem_charge(sk, frag->size);
		get_page(skb_frag_page(frag));
	}
	sg_mark_end(&offload_ctx->sg_tx_data[record->num_frags - 1]);

	/* all ready, send */
	return tls_push_sg(sk, ctx, offload_ctx->sg_tx_data, 0, flags);
}