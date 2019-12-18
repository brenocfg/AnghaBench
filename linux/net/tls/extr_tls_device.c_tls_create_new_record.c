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
struct tls_record_info {int num_frags; size_t len; int /*<<< orphan*/ * frags; } ;
struct tls_offload_context_tx {struct tls_record_info* open_record; } ;
struct page_frag {size_t offset; int /*<<< orphan*/  page; } ;
typedef  int /*<<< orphan*/  skb_frag_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  __skb_frag_set_page (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_page (int /*<<< orphan*/ ) ; 
 struct tls_record_info* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_frag_off_set (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  skb_frag_size_set (int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static int tls_create_new_record(struct tls_offload_context_tx *offload_ctx,
				 struct page_frag *pfrag,
				 size_t prepend_size)
{
	struct tls_record_info *record;
	skb_frag_t *frag;

	record = kmalloc(sizeof(*record), GFP_KERNEL);
	if (!record)
		return -ENOMEM;

	frag = &record->frags[0];
	__skb_frag_set_page(frag, pfrag->page);
	skb_frag_off_set(frag, pfrag->offset);
	skb_frag_size_set(frag, prepend_size);

	get_page(pfrag->page);
	pfrag->offset += prepend_size;

	record->num_frags = 1;
	record->len = prepend_size;
	offload_ctx->open_record = record;
	return 0;
}