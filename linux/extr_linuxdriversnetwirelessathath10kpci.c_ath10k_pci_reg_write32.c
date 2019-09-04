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
struct ath10k {int dummy; } ;

/* Variables and functions */
 scalar_t__ PCIE_LOCAL_BASE_ADDRESS ; 
 int /*<<< orphan*/  ath10k_pci_write32 (struct ath10k*,scalar_t__,scalar_t__) ; 

void ath10k_pci_reg_write32(struct ath10k *ar, u32 addr, u32 val)
{
	ath10k_pci_write32(ar, PCIE_LOCAL_BASE_ADDRESS + addr, val);
}