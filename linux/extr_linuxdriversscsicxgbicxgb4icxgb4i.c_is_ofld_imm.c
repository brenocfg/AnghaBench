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
struct sk_buff {int len; } ;
struct fw_ofld_tx_data_wr {int dummy; } ;

/* Variables and functions */
 int MAX_IMM_TX_PKT_LEN ; 
 int /*<<< orphan*/  SKCBF_TX_NEED_HDR ; 
 int /*<<< orphan*/  cxgbi_skcb_test_flag (struct sk_buff const*,int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool is_ofld_imm(const struct sk_buff *skb)
{
	int len = skb->len;

	if (likely(cxgbi_skcb_test_flag(skb, SKCBF_TX_NEED_HDR)))
		len += sizeof(struct fw_ofld_tx_data_wr);

	return len <= MAX_IMM_TX_PKT_LEN;
}