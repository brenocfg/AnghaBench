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
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u32 ;
struct ath10k_pci {scalar_t__ mem; } ;
struct ath10k_mem_region {scalar_t__ len; scalar_t__ start; } ;
struct ath10k {int dummy; } ;

/* Variables and functions */
 struct ath10k_pci* ath10k_pci_priv (struct ath10k*) ; 
 scalar_t__ ioread32 (scalar_t__) ; 

__attribute__((used)) static int ath10k_pci_dump_memory_reg(struct ath10k *ar,
				      const struct ath10k_mem_region *region,
				      u8 *buf)
{
	struct ath10k_pci *ar_pci = ath10k_pci_priv(ar);
	u32 i;

	for (i = 0; i < region->len; i += 4)
		*(u32 *)(buf + i) = ioread32(ar_pci->mem + region->start + i);

	return region->len;
}