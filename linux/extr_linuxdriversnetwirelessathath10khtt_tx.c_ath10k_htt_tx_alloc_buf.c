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
struct ath10k_htt {struct ath10k* ar; } ;
struct ath10k {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ath10k_err (struct ath10k*,char*,int) ; 
 int ath10k_htt_alloc_frag_desc (struct ath10k_htt*) ; 
 int ath10k_htt_alloc_txbuff (struct ath10k_htt*) ; 
 int /*<<< orphan*/  ath10k_htt_free_frag_desc (struct ath10k_htt*) ; 
 int /*<<< orphan*/  ath10k_htt_free_txbuff (struct ath10k_htt*) ; 
 int ath10k_htt_tx_alloc_txdone_fifo (struct ath10k_htt*) ; 
 int ath10k_htt_tx_alloc_txq (struct ath10k_htt*) ; 
 int /*<<< orphan*/  ath10k_htt_tx_free_txq (struct ath10k_htt*) ; 

__attribute__((used)) static int ath10k_htt_tx_alloc_buf(struct ath10k_htt *htt)
{
	struct ath10k *ar = htt->ar;
	int ret;

	ret = ath10k_htt_alloc_txbuff(htt);
	if (ret) {
		ath10k_err(ar, "failed to alloc cont tx buffer: %d\n", ret);
		return ret;
	}

	ret = ath10k_htt_alloc_frag_desc(htt);
	if (ret) {
		ath10k_err(ar, "failed to alloc cont frag desc: %d\n", ret);
		goto free_txbuf;
	}

	ret = ath10k_htt_tx_alloc_txq(htt);
	if (ret) {
		ath10k_err(ar, "failed to alloc txq: %d\n", ret);
		goto free_frag_desc;
	}

	ret = ath10k_htt_tx_alloc_txdone_fifo(htt);
	if (ret) {
		ath10k_err(ar, "failed to alloc txdone fifo: %d\n", ret);
		goto free_txq;
	}

	return 0;

free_txq:
	ath10k_htt_tx_free_txq(htt);

free_frag_desc:
	ath10k_htt_free_frag_desc(htt);

free_txbuf:
	ath10k_htt_free_txbuff(htt);

	return ret;
}