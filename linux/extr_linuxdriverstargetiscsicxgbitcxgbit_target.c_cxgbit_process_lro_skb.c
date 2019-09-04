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
typedef  int u8 ;
struct sk_buff {int dummy; } ;
struct cxgbit_sock {struct sk_buff* lro_hskb; } ;
struct cxgbit_lro_pdu_cb {int flags; int /*<<< orphan*/  complete; } ;
struct cxgbit_lro_cb {int pdu_idx; int /*<<< orphan*/  complete; } ;

/* Variables and functions */
 int PDUCBF_RX_STATUS ; 
 int /*<<< orphan*/  cxgbit_lro_hskb_reset (struct cxgbit_sock*) ; 
 int /*<<< orphan*/  cxgbit_lro_skb_merge (struct cxgbit_sock*,struct sk_buff*,int) ; 
 int cxgbit_process_iscsi_pdu (struct cxgbit_sock*,struct sk_buff*,int) ; 
 struct cxgbit_lro_cb* cxgbit_skb_lro_cb (struct sk_buff*) ; 
 struct cxgbit_lro_pdu_cb* cxgbit_skb_lro_pdu_cb (struct sk_buff*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cxgbit_process_lro_skb(struct cxgbit_sock *csk, struct sk_buff *skb)
{
	struct cxgbit_lro_cb *lro_cb = cxgbit_skb_lro_cb(skb);
	struct cxgbit_lro_pdu_cb *pdu_cb = cxgbit_skb_lro_pdu_cb(skb, 0);
	u8 pdu_idx = 0, last_idx = 0;
	int ret = 0;

	if (!pdu_cb->complete) {
		cxgbit_lro_skb_merge(csk, skb, 0);

		if (pdu_cb->flags & PDUCBF_RX_STATUS) {
			struct sk_buff *hskb = csk->lro_hskb;

			ret = cxgbit_process_iscsi_pdu(csk, hskb, 0);

			cxgbit_lro_hskb_reset(csk);

			if (ret < 0)
				goto out;
		}

		pdu_idx = 1;
	}

	if (lro_cb->pdu_idx)
		last_idx = lro_cb->pdu_idx - 1;

	for (; pdu_idx <= last_idx; pdu_idx++) {
		ret = cxgbit_process_iscsi_pdu(csk, skb, pdu_idx);
		if (ret < 0)
			goto out;
	}

	if ((!lro_cb->complete) && lro_cb->pdu_idx)
		cxgbit_lro_skb_merge(csk, skb, lro_cb->pdu_idx);

out:
	return ret;
}