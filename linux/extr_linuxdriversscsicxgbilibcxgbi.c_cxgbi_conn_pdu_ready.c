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
struct sk_buff {unsigned int copied_seq; int /*<<< orphan*/  len; int /*<<< orphan*/  receive_queue; struct iscsi_conn* user_data; struct cxgbi_device* cdev; } ;
struct iscsi_conn {int suspend_rx; int id; unsigned int rxdata_octets; } ;
struct cxgbi_sock {unsigned int copied_seq; int /*<<< orphan*/  len; int /*<<< orphan*/  receive_queue; struct iscsi_conn* user_data; struct cxgbi_device* cdev; } ;
struct cxgbi_device {scalar_t__ skb_rx_extra; } ;

/* Variables and functions */
 int CXGBI_DBG_PDU_RX ; 
 int EIO ; 
 int /*<<< orphan*/  ISCSI_ERR_CONN_FAILED ; 
 int /*<<< orphan*/  SKCBF_RX_COALESCED ; 
 int /*<<< orphan*/  SKCBF_RX_DATA ; 
 int /*<<< orphan*/  SKCBF_RX_STATUS ; 
 int /*<<< orphan*/  __kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  __skb_unlink (struct sk_buff*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  csk_return_rx_credits (struct sk_buff*,unsigned int) ; 
 unsigned int cxgbi_skcb_flags (struct sk_buff*) ; 
 scalar_t__ cxgbi_skcb_rx_pdulen (struct sk_buff*) ; 
 scalar_t__ cxgbi_skcb_test_flag (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iscsi_conn_failure (struct iscsi_conn*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_debug (int,char*,struct sk_buff*,...) ; 
 int /*<<< orphan*/  pr_err (char*,struct sk_buff*,struct sk_buff*,int /*<<< orphan*/ ,unsigned int,scalar_t__,...) ; 
 int /*<<< orphan*/  pr_info (char*,struct sk_buff*,struct iscsi_conn*,int,unsigned int) ; 
 struct sk_buff* skb_peek (int /*<<< orphan*/ *) ; 
 int skb_read_pdu_bhs (struct sk_buff*,struct iscsi_conn*,struct sk_buff*) ; 
 int skb_read_pdu_data (struct iscsi_conn*,struct sk_buff*,struct sk_buff*,scalar_t__) ; 
 scalar_t__ unlikely (int) ; 

void cxgbi_conn_pdu_ready(struct cxgbi_sock *csk)
{
	struct cxgbi_device *cdev = csk->cdev;
	struct iscsi_conn *conn = csk->user_data;
	struct sk_buff *skb;
	unsigned int read = 0;
	int err = 0;

	log_debug(1 << CXGBI_DBG_PDU_RX,
		"csk 0x%p, conn 0x%p.\n", csk, conn);

	if (unlikely(!conn || conn->suspend_rx)) {
		log_debug(1 << CXGBI_DBG_PDU_RX,
			"csk 0x%p, conn 0x%p, id %d, suspend_rx %lu!\n",
			csk, conn, conn ? conn->id : 0xFF,
			conn ? conn->suspend_rx : 0xFF);
		return;
	}

	while (!err) {
		skb = skb_peek(&csk->receive_queue);
		if (!skb ||
		    !(cxgbi_skcb_test_flag(skb, SKCBF_RX_STATUS))) {
			if (skb)
				log_debug(1 << CXGBI_DBG_PDU_RX,
					"skb 0x%p, NOT ready 0x%lx.\n",
					skb, cxgbi_skcb_flags(skb));
			break;
		}
		__skb_unlink(skb, &csk->receive_queue);

		read += cxgbi_skcb_rx_pdulen(skb);
		log_debug(1 << CXGBI_DBG_PDU_RX,
			"csk 0x%p, skb 0x%p,%u,f 0x%lx, pdu len %u.\n",
			csk, skb, skb->len, cxgbi_skcb_flags(skb),
			cxgbi_skcb_rx_pdulen(skb));

		if (cxgbi_skcb_test_flag(skb, SKCBF_RX_COALESCED)) {
			err = skb_read_pdu_bhs(csk, conn, skb);
			if (err < 0) {
				pr_err("coalesced bhs, csk 0x%p, skb 0x%p,%u, "
					"f 0x%lx, plen %u.\n",
					csk, skb, skb->len,
					cxgbi_skcb_flags(skb),
					cxgbi_skcb_rx_pdulen(skb));
				goto skb_done;
			}
			err = skb_read_pdu_data(conn, skb, skb,
						err + cdev->skb_rx_extra);
			if (err < 0)
				pr_err("coalesced data, csk 0x%p, skb 0x%p,%u, "
					"f 0x%lx, plen %u.\n",
					csk, skb, skb->len,
					cxgbi_skcb_flags(skb),
					cxgbi_skcb_rx_pdulen(skb));
		} else {
			err = skb_read_pdu_bhs(csk, conn, skb);
			if (err < 0) {
				pr_err("bhs, csk 0x%p, skb 0x%p,%u, "
					"f 0x%lx, plen %u.\n",
					csk, skb, skb->len,
					cxgbi_skcb_flags(skb),
					cxgbi_skcb_rx_pdulen(skb));
				goto skb_done;
			}

			if (cxgbi_skcb_test_flag(skb, SKCBF_RX_DATA)) {
				struct sk_buff *dskb;

				dskb = skb_peek(&csk->receive_queue);
				if (!dskb) {
					pr_err("csk 0x%p, skb 0x%p,%u, f 0x%lx,"
						" plen %u, NO data.\n",
						csk, skb, skb->len,
						cxgbi_skcb_flags(skb),
						cxgbi_skcb_rx_pdulen(skb));
					err = -EIO;
					goto skb_done;
				}
				__skb_unlink(dskb, &csk->receive_queue);

				err = skb_read_pdu_data(conn, skb, dskb, 0);
				if (err < 0)
					pr_err("data, csk 0x%p, skb 0x%p,%u, "
						"f 0x%lx, plen %u, dskb 0x%p,"
						"%u.\n",
						csk, skb, skb->len,
						cxgbi_skcb_flags(skb),
						cxgbi_skcb_rx_pdulen(skb),
						dskb, dskb->len);
				__kfree_skb(dskb);
			} else
				err = skb_read_pdu_data(conn, skb, skb, 0);
		}
skb_done:
		__kfree_skb(skb);

		if (err < 0)
			break;
	}

	log_debug(1 << CXGBI_DBG_PDU_RX, "csk 0x%p, read %u.\n", csk, read);
	if (read) {
		csk->copied_seq += read;
		csk_return_rx_credits(csk, read);
		conn->rxdata_octets += read;
	}

	if (err < 0) {
		pr_info("csk 0x%p, 0x%p, rx failed %d, read %u.\n",
			csk, conn, err, read);
		iscsi_conn_failure(conn, ISCSI_ERR_CONN_FAILED);
	}
}