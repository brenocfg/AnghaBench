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
struct tls_record_info {int num_frags; int len; int /*<<< orphan*/ * frags; } ;
struct page_frag {scalar_t__ offset; int /*<<< orphan*/  page; } ;
typedef  int /*<<< orphan*/  skb_frag_t ;

/* Variables and functions */
 int /*<<< orphan*/  __skb_frag_set_page (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_page (int /*<<< orphan*/ ) ; 
 scalar_t__ skb_frag_off (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_frag_off_set (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  skb_frag_page (int /*<<< orphan*/ *) ; 
 scalar_t__ skb_frag_size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_frag_size_add (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  skb_frag_size_set (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void tls_append_frag(struct tls_record_info *record,
			    struct page_frag *pfrag,
			    int size)
{
	skb_frag_t *frag;

	frag = &record->frags[record->num_frags - 1];
	if (skb_frag_page(frag) == pfrag->page &&
	    skb_frag_off(frag) + skb_frag_size(frag) == pfrag->offset) {
		skb_frag_size_add(frag, size);
	} else {
		++frag;
		__skb_frag_set_page(frag, pfrag->page);
		skb_frag_off_set(frag, pfrag->offset);
		skb_frag_size_set(frag, size);
		++record->num_frags;
		get_page(pfrag->page);
	}

	pfrag->offset += size;
	record->len += size;
}