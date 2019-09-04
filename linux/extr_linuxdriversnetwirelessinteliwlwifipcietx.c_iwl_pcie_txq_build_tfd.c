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
typedef  scalar_t__ u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct iwl_txq {int write_ptr; void* tfds; } ;
struct iwl_trans_pcie {int tfd_size; scalar_t__ max_tbs; } ;
struct iwl_trans {int dummy; } ;
typedef  int dma_addr_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  IWL_ERR (struct iwl_trans*,char*,scalar_t__) ; 
 struct iwl_trans_pcie* IWL_TRANS_GET_PCIE_TRANS (struct iwl_trans*) ; 
 int IWL_TX_DMA_MASK ; 
 scalar_t__ WARN (int,char*,unsigned long long) ; 
 scalar_t__ iwl_pcie_tfd_get_num_tbs (struct iwl_trans*,void*) ; 
 int /*<<< orphan*/  iwl_pcie_tfd_set_tb (struct iwl_trans*,void*,scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int iwl_pcie_txq_build_tfd(struct iwl_trans *trans, struct iwl_txq *txq,
				  dma_addr_t addr, u16 len, bool reset)
{
	struct iwl_trans_pcie *trans_pcie = IWL_TRANS_GET_PCIE_TRANS(trans);
	void *tfd;
	u32 num_tbs;

	tfd = txq->tfds + trans_pcie->tfd_size * txq->write_ptr;

	if (reset)
		memset(tfd, 0, trans_pcie->tfd_size);

	num_tbs = iwl_pcie_tfd_get_num_tbs(trans, tfd);

	/* Each TFD can point to a maximum max_tbs Tx buffers */
	if (num_tbs >= trans_pcie->max_tbs) {
		IWL_ERR(trans, "Error can not send more than %d chunks\n",
			trans_pcie->max_tbs);
		return -EINVAL;
	}

	if (WARN(addr & ~IWL_TX_DMA_MASK,
		 "Unaligned address = %llx\n", (unsigned long long)addr))
		return -EINVAL;

	iwl_pcie_tfd_set_tb(trans, tfd, num_tbs, addr, len);

	return num_tbs;
}