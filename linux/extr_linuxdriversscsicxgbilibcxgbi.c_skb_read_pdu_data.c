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
struct sk_buff {int /*<<< orphan*/  len; } ;
struct TYPE_4__ {int /*<<< orphan*/  datalen; TYPE_1__* hdr; } ;
struct iscsi_tcp_conn {TYPE_2__ in; } ;
struct iscsi_conn {scalar_t__ hdrdgst_en; scalar_t__ datadgst_en; struct iscsi_tcp_conn* dd_data; } ;
struct TYPE_3__ {int opcode; int /*<<< orphan*/  itt; } ;

/* Variables and functions */
 int CXGBI_DBG_PDU_RX ; 
 int EIO ; 
 scalar_t__ ISCSI_DIGEST_SIZE ; 
 int /*<<< orphan*/  ISCSI_ERR_DATA_DGST ; 
 int ISCSI_OPCODE_MASK ; 
 int ISCSI_OP_SCSI_DATA_IN ; 
 int /*<<< orphan*/  SKCBF_RX_DATA_DDPD ; 
 int /*<<< orphan*/  SKCBF_RX_DCRC_ERR ; 
 int /*<<< orphan*/  cxgbi_skcb_flags (struct sk_buff*) ; 
 scalar_t__ cxgbi_skcb_test_flag (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iscsi_conn_failure (struct iscsi_conn*,int /*<<< orphan*/ ) ; 
 scalar_t__ iscsi_tcp_recv_segment_is_hdr (struct iscsi_tcp_conn*) ; 
 int /*<<< orphan*/  log_debug (int,char*,...) ; 
 int /*<<< orphan*/  ntohl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_info (char*,struct iscsi_conn*,struct sk_buff*,int /*<<< orphan*/ ) ; 
 int read_pdu_skb (struct iscsi_conn*,struct sk_buff*,unsigned int,int) ; 

__attribute__((used)) static int skb_read_pdu_data(struct iscsi_conn *conn, struct sk_buff *lskb,
			     struct sk_buff *skb, unsigned int offset)
{
	struct iscsi_tcp_conn *tcp_conn = conn->dd_data;
	bool offloaded = 0;
	int opcode = tcp_conn->in.hdr->opcode & ISCSI_OPCODE_MASK;

	log_debug(1 << CXGBI_DBG_PDU_RX,
		"conn 0x%p, skb 0x%p, len %u, flag 0x%lx.\n",
		conn, skb, skb->len, cxgbi_skcb_flags(skb));

	if (conn->datadgst_en &&
	    cxgbi_skcb_test_flag(lskb, SKCBF_RX_DCRC_ERR)) {
		pr_info("conn 0x%p, skb 0x%p, dcrc 0x%lx.\n",
			conn, lskb, cxgbi_skcb_flags(lskb));
		iscsi_conn_failure(conn, ISCSI_ERR_DATA_DGST);
		return -EIO;
	}

	if (iscsi_tcp_recv_segment_is_hdr(tcp_conn))
		return 0;

	/* coalesced, add header digest length */
	if (lskb == skb && conn->hdrdgst_en)
		offset += ISCSI_DIGEST_SIZE;

	if (cxgbi_skcb_test_flag(lskb, SKCBF_RX_DATA_DDPD))
		offloaded = 1;

	if (opcode == ISCSI_OP_SCSI_DATA_IN)
		log_debug(1 << CXGBI_DBG_PDU_RX,
			"skb 0x%p, op 0x%x, itt 0x%x, %u %s ddp'ed.\n",
			skb, opcode, ntohl(tcp_conn->in.hdr->itt),
			tcp_conn->in.datalen, offloaded ? "is" : "not");

	return read_pdu_skb(conn, skb, offset, offloaded);
}