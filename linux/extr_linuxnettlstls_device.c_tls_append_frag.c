#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct tls_record_info {int num_frags; int len; TYPE_2__* frags; } ;
struct page_frag {scalar_t__ page; scalar_t__ offset; } ;
struct TYPE_3__ {scalar_t__ p; } ;
struct TYPE_4__ {scalar_t__ page_offset; int size; TYPE_1__ page; } ;
typedef  TYPE_2__ skb_frag_t ;

/* Variables and functions */
 int /*<<< orphan*/  get_page (scalar_t__) ; 

__attribute__((used)) static void tls_append_frag(struct tls_record_info *record,
			    struct page_frag *pfrag,
			    int size)
{
	skb_frag_t *frag;

	frag = &record->frags[record->num_frags - 1];
	if (frag->page.p == pfrag->page &&
	    frag->page_offset + frag->size == pfrag->offset) {
		frag->size += size;
	} else {
		++frag;
		frag->page.p = pfrag->page;
		frag->page_offset = pfrag->offset;
		frag->size = size;
		++record->num_frags;
		get_page(pfrag->page);
	}

	pfrag->offset += size;
	record->len += size;
}