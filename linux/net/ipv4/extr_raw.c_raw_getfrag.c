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
struct sk_buff {scalar_t__ ip_summed; int /*<<< orphan*/  csum; } ;
struct TYPE_2__ {scalar_t__ c; } ;
struct raw_frag_vec {int hlen; int /*<<< orphan*/  msg; TYPE_1__ hdr; } ;

/* Variables and functions */
 scalar_t__ CHECKSUM_PARTIAL ; 
 int /*<<< orphan*/  csum_block_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  csum_partial_copy_nocheck (scalar_t__,char*,int,int /*<<< orphan*/ ) ; 
 int ip_generic_getfrag (int /*<<< orphan*/ ,char*,int,int,int,struct sk_buff*) ; 
 int /*<<< orphan*/  memcpy (char*,scalar_t__,int) ; 
 int min (int,int) ; 

__attribute__((used)) static int raw_getfrag(void *from, char *to, int offset, int len, int odd,
		       struct sk_buff *skb)
{
	struct raw_frag_vec *rfv = from;

	if (offset < rfv->hlen) {
		int copy = min(rfv->hlen - offset, len);

		if (skb->ip_summed == CHECKSUM_PARTIAL)
			memcpy(to, rfv->hdr.c + offset, copy);
		else
			skb->csum = csum_block_add(
				skb->csum,
				csum_partial_copy_nocheck(rfv->hdr.c + offset,
							  to, copy, 0),
				odd);

		odd = 0;
		offset += copy;
		to += copy;
		len -= copy;

		if (!len)
			return 0;
	}

	offset -= rfv->hlen;

	return ip_generic_getfrag(rfv->msg, to, offset, len, odd, skb);
}