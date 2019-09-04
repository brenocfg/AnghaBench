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
struct sk_buff {char* data; } ;
struct qeth_qdio_out_buffer {int next_element_to_fill; struct qdio_buffer* buffer; } ;
struct qdio_buffer {TYPE_1__* element; } ;
typedef  int /*<<< orphan*/  skb_frag_t ;
struct TYPE_4__ {int nr_frags; int /*<<< orphan*/ * frags; } ;
struct TYPE_3__ {char* addr; int length; void* eflags; } ;

/* Variables and functions */
 unsigned long PAGE_SIZE ; 
 void* SBAL_EFLAGS_FIRST_FRAG ; 
 void* SBAL_EFLAGS_LAST_FRAG ; 
 void* SBAL_EFLAGS_MIDDLE_FRAG ; 
 char* skb_frag_address (int /*<<< orphan*/ *) ; 
 int skb_frag_size (int /*<<< orphan*/ *) ; 
 unsigned int skb_headlen (struct sk_buff*) ; 
 scalar_t__ skb_is_nonlinear (struct sk_buff*) ; 
 TYPE_2__* skb_shinfo (struct sk_buff*) ; 

__attribute__((used)) static void __qeth_fill_buffer(struct sk_buff *skb,
			       struct qeth_qdio_out_buffer *buf,
			       bool is_first_elem, unsigned int offset)
{
	struct qdio_buffer *buffer = buf->buffer;
	int element = buf->next_element_to_fill;
	int length = skb_headlen(skb) - offset;
	char *data = skb->data + offset;
	int length_here, cnt;

	/* map linear part into buffer element(s) */
	while (length > 0) {
		/* length_here is the remaining amount of data in this page */
		length_here = PAGE_SIZE - ((unsigned long) data % PAGE_SIZE);
		if (length < length_here)
			length_here = length;

		buffer->element[element].addr = data;
		buffer->element[element].length = length_here;
		length -= length_here;
		if (is_first_elem) {
			is_first_elem = false;
			if (length || skb_is_nonlinear(skb))
				/* skb needs additional elements */
				buffer->element[element].eflags =
					SBAL_EFLAGS_FIRST_FRAG;
			else
				buffer->element[element].eflags = 0;
		} else {
			buffer->element[element].eflags =
				SBAL_EFLAGS_MIDDLE_FRAG;
		}
		data += length_here;
		element++;
	}

	/* map page frags into buffer element(s) */
	for (cnt = 0; cnt < skb_shinfo(skb)->nr_frags; cnt++) {
		skb_frag_t *frag = &skb_shinfo(skb)->frags[cnt];

		data = skb_frag_address(frag);
		length = skb_frag_size(frag);
		while (length > 0) {
			length_here = PAGE_SIZE -
				((unsigned long) data % PAGE_SIZE);
			if (length < length_here)
				length_here = length;

			buffer->element[element].addr = data;
			buffer->element[element].length = length_here;
			buffer->element[element].eflags =
				SBAL_EFLAGS_MIDDLE_FRAG;
			length -= length_here;
			data += length_here;
			element++;
		}
	}

	if (buffer->element[element - 1].eflags)
		buffer->element[element - 1].eflags = SBAL_EFLAGS_LAST_FRAG;
	buf->next_element_to_fill = element;
}