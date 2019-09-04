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
typedef  int /*<<< orphan*/  u32 ;
struct ce_desc {int /*<<< orphan*/  flags; int /*<<< orphan*/  nbytes; int /*<<< orphan*/  addr; } ;
struct ath10k_ce_ring {struct ce_desc* base_addr_owner_space; } ;
struct ath10k {int dummy; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  CE_DESC_FLAGS_META_DATA ; 
 struct ce_desc* CE_SRC_RING_TO_DESC (struct ce_desc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ath10k_ce_extract_desc_data(struct ath10k *ar,
					struct ath10k_ce_ring *src_ring,
					u32 sw_index,
					dma_addr_t *bufferp,
					u32 *nbytesp,
					u32 *transfer_idp)
{
		struct ce_desc *base = src_ring->base_addr_owner_space;
		struct ce_desc *desc = CE_SRC_RING_TO_DESC(base, sw_index);

		/* Return data from completed source descriptor */
		*bufferp = __le32_to_cpu(desc->addr);
		*nbytesp = __le16_to_cpu(desc->nbytes);
		*transfer_idp = MS(__le16_to_cpu(desc->flags),
				   CE_DESC_FLAGS_META_DATA);
}