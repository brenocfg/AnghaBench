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
struct x25_neigh {scalar_t__ extended; } ;
struct sk_buff {int /*<<< orphan*/ * sk; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  X25_CLEAR_REQUEST ; 
 unsigned int X25_GFI_EXTSEQ ; 
 unsigned int X25_GFI_STDSEQ ; 
 int X25_MAX_L2_LEN ; 
 int X25_STD_MIN_LEN ; 
 struct sk_buff* alloc_skb (int,int /*<<< orphan*/ ) ; 
 unsigned char* skb_put (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,int) ; 
 int /*<<< orphan*/  x25_send_frame (struct sk_buff*,struct x25_neigh*) ; 

void x25_transmit_clear_request(struct x25_neigh *nb, unsigned int lci,
				unsigned char cause)
{
	unsigned char *dptr;
	int len = X25_MAX_L2_LEN + X25_STD_MIN_LEN + 2;
	struct sk_buff *skb = alloc_skb(len, GFP_ATOMIC);

	if (!skb)
		return;

	skb_reserve(skb, X25_MAX_L2_LEN);

	dptr = skb_put(skb, X25_STD_MIN_LEN + 2);

	*dptr++ = ((lci >> 8) & 0x0F) | (nb->extended ?
					 X25_GFI_EXTSEQ :
					 X25_GFI_STDSEQ);
	*dptr++ = (lci >> 0) & 0xFF;
	*dptr++ = X25_CLEAR_REQUEST;
	*dptr++ = cause;
	*dptr++ = 0x00;

	skb->sk = NULL;

	x25_send_frame(skb, nb);
}