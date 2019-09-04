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
struct ath10k {int dummy; } ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int /*<<< orphan*/  ATH10K_DBG_HTT ; 
 int /*<<< orphan*/  ath10k_dbg (struct ath10k*,int /*<<< orphan*/ ,char*,int) ; 
 int le32_to_cpu (int /*<<< orphan*/  const) ; 

__attribute__((used)) static void ath10k_htt_rx_tx_fetch_resp_id_confirm(struct ath10k *ar,
						   const __le32 *resp_ids,
						   int num_resp_ids)
{
	int i;
	u32 resp_id;

	ath10k_dbg(ar, ATH10K_DBG_HTT, "htt rx tx fetch confirm num_resp_ids %d\n",
		   num_resp_ids);

	for (i = 0; i < num_resp_ids; i++) {
		resp_id = le32_to_cpu(resp_ids[i]);

		ath10k_dbg(ar, ATH10K_DBG_HTT, "htt rx tx fetch confirm resp_id %u\n",
			   resp_id);

		/* TODO: free resp_id */
	}
}