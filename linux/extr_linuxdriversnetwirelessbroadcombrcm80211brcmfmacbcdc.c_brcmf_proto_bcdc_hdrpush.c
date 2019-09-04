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
typedef  int /*<<< orphan*/  u8 ;
struct sk_buff {scalar_t__ ip_summed; int priority; scalar_t__ data; } ;
struct brcmf_pub {int dummy; } ;
struct brcmf_proto_bcdc_header {int flags; int priority; int /*<<< orphan*/  data_offset; scalar_t__ flags2; } ;

/* Variables and functions */
 int /*<<< orphan*/  BCDC ; 
 int BCDC_FLAG_SUM_NEEDED ; 
 int BCDC_FLAG_VER_SHIFT ; 
 int /*<<< orphan*/  BCDC_HEADER_LEN ; 
 int BCDC_PRIORITY_MASK ; 
 int BCDC_PROTO_VER ; 
 int /*<<< orphan*/  BCDC_SET_IF_IDX (struct brcmf_proto_bcdc_header*,int) ; 
 scalar_t__ CHECKSUM_PARTIAL ; 
 int /*<<< orphan*/  brcmf_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  skb_push (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_brcmf_bcdchdr (scalar_t__) ; 

__attribute__((used)) static void
brcmf_proto_bcdc_hdrpush(struct brcmf_pub *drvr, int ifidx, u8 offset,
			 struct sk_buff *pktbuf)
{
	struct brcmf_proto_bcdc_header *h;

	brcmf_dbg(BCDC, "Enter\n");

	/* Push BDC header used to convey priority for buses that don't */
	skb_push(pktbuf, BCDC_HEADER_LEN);

	h = (struct brcmf_proto_bcdc_header *)(pktbuf->data);

	h->flags = (BCDC_PROTO_VER << BCDC_FLAG_VER_SHIFT);
	if (pktbuf->ip_summed == CHECKSUM_PARTIAL)
		h->flags |= BCDC_FLAG_SUM_NEEDED;

	h->priority = (pktbuf->priority & BCDC_PRIORITY_MASK);
	h->flags2 = 0;
	h->data_offset = offset;
	BCDC_SET_IF_IDX(h, ifidx);
	trace_brcmf_bcdchdr(pktbuf->data);
}