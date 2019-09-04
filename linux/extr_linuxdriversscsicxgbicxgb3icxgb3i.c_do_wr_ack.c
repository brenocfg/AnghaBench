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
struct t3cdev {int dummy; } ;
struct sk_buff {int dummy; } ;
struct cxgbi_sock {int /*<<< orphan*/  tid; int /*<<< orphan*/  flags; int /*<<< orphan*/  state; } ;
struct cpl_wr_ack {int /*<<< orphan*/  snd_una; int /*<<< orphan*/  credits; } ;

/* Variables and functions */
 int CXGBI_DBG_PDU_RX ; 
 int CXGBI_DBG_TOE ; 
 int /*<<< orphan*/  __kfree_skb (struct sk_buff*) ; 
 struct cpl_wr_ack* cplhdr (struct sk_buff*) ; 
 int /*<<< orphan*/  cxgbi_sock_rcv_wr_ack (struct cxgbi_sock*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  log_debug (int,char*,struct cxgbi_sock*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntohl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int do_wr_ack(struct t3cdev *cdev, struct sk_buff *skb, void *ctx)
{
	struct cxgbi_sock *csk = ctx;
	struct cpl_wr_ack *hdr = cplhdr(skb);

	log_debug(1 << CXGBI_DBG_TOE | 1 << CXGBI_DBG_PDU_RX,
		"csk 0x%p,%u,0x%lx,%u, cr %u.\n",
		csk, csk->state, csk->flags, csk->tid, ntohs(hdr->credits));

	cxgbi_sock_rcv_wr_ack(csk, ntohs(hdr->credits), ntohl(hdr->snd_una), 1);
	__kfree_skb(skb);
	return 0;
}