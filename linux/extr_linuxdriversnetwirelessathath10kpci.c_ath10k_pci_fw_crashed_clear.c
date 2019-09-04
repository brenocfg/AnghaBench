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
struct ath10k {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FW_INDICATOR_ADDRESS ; 
 int /*<<< orphan*/  FW_IND_EVENT_PENDING ; 
 int /*<<< orphan*/  ath10k_pci_read32 (struct ath10k*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath10k_pci_write32 (struct ath10k*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ath10k_pci_fw_crashed_clear(struct ath10k *ar)
{
	u32 val;

	val = ath10k_pci_read32(ar, FW_INDICATOR_ADDRESS);
	val &= ~FW_IND_EVENT_PENDING;
	ath10k_pci_write32(ar, FW_INDICATOR_ADDRESS, val);
}