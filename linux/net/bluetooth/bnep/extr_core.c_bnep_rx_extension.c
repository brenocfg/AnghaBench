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
struct sk_buff {int /*<<< orphan*/  len; scalar_t__ data; } ;
struct bnep_session {int dummy; } ;
struct bnep_ext_hdr {int type; int len; } ;

/* Variables and functions */
#define  BNEP_EXT_CONTROL 128 
 int BNEP_EXT_HEADER ; 
 int BNEP_TYPE_MASK ; 
 int /*<<< orphan*/  BT_DBG (char*,int,int) ; 
 int EILSEQ ; 
 int /*<<< orphan*/  bnep_rx_control (struct bnep_session*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int) ; 

__attribute__((used)) static int bnep_rx_extension(struct bnep_session *s, struct sk_buff *skb)
{
	struct bnep_ext_hdr *h;
	int err = 0;

	do {
		h = (void *) skb->data;
		if (!skb_pull(skb, sizeof(*h))) {
			err = -EILSEQ;
			break;
		}

		BT_DBG("type 0x%x len %d", h->type, h->len);

		switch (h->type & BNEP_TYPE_MASK) {
		case BNEP_EXT_CONTROL:
			bnep_rx_control(s, skb->data, skb->len);
			break;

		default:
			/* Unknown extension, skip it. */
			break;
		}

		if (!skb_pull(skb, h->len)) {
			err = -EILSEQ;
			break;
		}
	} while (!err && (h->type & BNEP_EXT_HEADER));

	return err;
}