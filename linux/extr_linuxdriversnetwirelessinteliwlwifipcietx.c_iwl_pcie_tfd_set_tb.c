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
typedef  size_t u8 ;
typedef  int u16 ;
struct iwl_trans {int dummy; } ;
struct iwl_tfd_tb {int /*<<< orphan*/  hi_n_len; int /*<<< orphan*/  lo; } ;
struct iwl_tfd {size_t num_tbs; struct iwl_tfd_tb* tbs; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 int iwl_get_dma_hi_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_unaligned_le32 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void iwl_pcie_tfd_set_tb(struct iwl_trans *trans, void *tfd,
				       u8 idx, dma_addr_t addr, u16 len)
{
	struct iwl_tfd *tfd_fh = (void *)tfd;
	struct iwl_tfd_tb *tb = &tfd_fh->tbs[idx];

	u16 hi_n_len = len << 4;

	put_unaligned_le32(addr, &tb->lo);
	hi_n_len |= iwl_get_dma_hi_addr(addr);

	tb->hi_n_len = cpu_to_le16(hi_n_len);

	tfd_fh->num_tbs = idx + 1;
}