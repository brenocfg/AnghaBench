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
struct tls_record_info {scalar_t__ len; int /*<<< orphan*/ * frags; } ;
struct tls_prot_info {int tag_size; scalar_t__ overhead_size; int /*<<< orphan*/  version; } ;
struct tls_context {struct tls_prot_info prot_info; } ;
struct sock {int /*<<< orphan*/  sk_allocation; } ;
struct page_frag {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_frag_address (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_page_frag_refill (int,struct page_frag*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tls_append_frag (struct tls_record_info*,struct page_frag*,int) ; 
 int /*<<< orphan*/  tls_fill_prepend (struct tls_context*,int /*<<< orphan*/ ,scalar_t__,unsigned char,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tls_device_record_close(struct sock *sk,
				   struct tls_context *ctx,
				   struct tls_record_info *record,
				   struct page_frag *pfrag,
				   unsigned char record_type)
{
	struct tls_prot_info *prot = &ctx->prot_info;
	int ret;

	/* append tag
	 * device will fill in the tag, we just need to append a placeholder
	 * use socket memory to improve coalescing (re-using a single buffer
	 * increases frag count)
	 * if we can't allocate memory now, steal some back from data
	 */
	if (likely(skb_page_frag_refill(prot->tag_size, pfrag,
					sk->sk_allocation))) {
		ret = 0;
		tls_append_frag(record, pfrag, prot->tag_size);
	} else {
		ret = prot->tag_size;
		if (record->len <= prot->overhead_size)
			return -ENOMEM;
	}

	/* fill prepend */
	tls_fill_prepend(ctx, skb_frag_address(&record->frags[0]),
			 record->len - prot->overhead_size,
			 record_type, prot->version);
	return ret;
}