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
typedef  int u32 ;
struct sk_buff {int dummy; } ;
struct cxgbi_sock {int dummy; } ;

/* Variables and functions */
 int CPL_RX_DDP_STATUS_DCRC_SHIFT ; 
 int CPL_RX_DDP_STATUS_DDP_SHIFT ; 
 int CPL_RX_DDP_STATUS_HCRC_SHIFT ; 
 int CPL_RX_DDP_STATUS_PAD_SHIFT ; 
 int CXGBI_DBG_PDU_RX ; 
 int /*<<< orphan*/  SKCBF_RX_DATA ; 
 int /*<<< orphan*/  SKCBF_RX_DATA_DDPD ; 
 int /*<<< orphan*/  SKCBF_RX_DCRC_ERR ; 
 int /*<<< orphan*/  SKCBF_RX_HCRC_ERR ; 
 int /*<<< orphan*/  SKCBF_RX_PAD_ERR ; 
 int /*<<< orphan*/  cxgbi_skcb_flags (struct sk_buff*) ; 
 int /*<<< orphan*/  cxgbi_skcb_set_flag (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cxgbi_skcb_test_flag (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_debug (int,char*,struct cxgbi_sock*,struct sk_buff*,int) ; 
 int /*<<< orphan*/  pr_info (char*,struct cxgbi_sock*,struct sk_buff*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
cxgb4i_process_ddpvld(struct cxgbi_sock *csk,
		      struct sk_buff *skb, u32 ddpvld)
{
	if (ddpvld & (1 << CPL_RX_DDP_STATUS_HCRC_SHIFT)) {
		pr_info("csk 0x%p, lhdr 0x%p, status 0x%x, hcrc bad 0x%lx.\n",
			csk, skb, ddpvld, cxgbi_skcb_flags(skb));
		cxgbi_skcb_set_flag(skb, SKCBF_RX_HCRC_ERR);
	}

	if (ddpvld & (1 << CPL_RX_DDP_STATUS_DCRC_SHIFT)) {
		pr_info("csk 0x%p, lhdr 0x%p, status 0x%x, dcrc bad 0x%lx.\n",
			csk, skb, ddpvld, cxgbi_skcb_flags(skb));
		cxgbi_skcb_set_flag(skb, SKCBF_RX_DCRC_ERR);
	}

	if (ddpvld & (1 << CPL_RX_DDP_STATUS_PAD_SHIFT)) {
		log_debug(1 << CXGBI_DBG_PDU_RX,
			  "csk 0x%p, lhdr 0x%p, status 0x%x, pad bad.\n",
			  csk, skb, ddpvld);
		cxgbi_skcb_set_flag(skb, SKCBF_RX_PAD_ERR);
	}

	if ((ddpvld & (1 << CPL_RX_DDP_STATUS_DDP_SHIFT)) &&
	    !cxgbi_skcb_test_flag(skb, SKCBF_RX_DATA)) {
		log_debug(1 << CXGBI_DBG_PDU_RX,
			  "csk 0x%p, lhdr 0x%p, 0x%x, data ddp'ed.\n",
			  csk, skb, ddpvld);
		cxgbi_skcb_set_flag(skb, SKCBF_RX_DATA_DDPD);
	}
}