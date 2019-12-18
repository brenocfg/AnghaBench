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
struct tso_t {int tcp_seq; scalar_t__ size; int data; size_t next_frag_idx; } ;
struct sk_buff {int dummy; } ;
typedef  int /*<<< orphan*/  skb_frag_t ;
struct TYPE_2__ {size_t nr_frags; int /*<<< orphan*/ * frags; } ;

/* Variables and functions */
 int skb_frag_address (int /*<<< orphan*/ *) ; 
 scalar_t__ skb_frag_size (int /*<<< orphan*/ *) ; 
 TYPE_1__* skb_shinfo (struct sk_buff*) ; 

void tso_build_data(struct sk_buff *skb, struct tso_t *tso, int size)
{
	tso->tcp_seq += size;
	tso->size -= size;
	tso->data += size;

	if ((tso->size == 0) &&
	    (tso->next_frag_idx < skb_shinfo(skb)->nr_frags)) {
		skb_frag_t *frag = &skb_shinfo(skb)->frags[tso->next_frag_idx];

		/* Move to next segment */
		tso->size = skb_frag_size(frag);
		tso->data = skb_frag_address(frag);
		tso->next_frag_idx++;
	}
}