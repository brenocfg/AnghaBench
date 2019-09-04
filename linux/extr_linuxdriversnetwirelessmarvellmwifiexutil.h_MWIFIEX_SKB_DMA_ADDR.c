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
struct sk_buff {int dummy; } ;
struct mwifiex_dma_mapping {int /*<<< orphan*/  addr; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  mwifiex_get_mapping (struct sk_buff*,struct mwifiex_dma_mapping*) ; 

__attribute__((used)) static inline dma_addr_t MWIFIEX_SKB_DMA_ADDR(struct sk_buff *skb)
{
	struct mwifiex_dma_mapping mapping;

	mwifiex_get_mapping(skb, &mapping);

	return mapping.addr;
}