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
typedef  int /*<<< orphan*/  val ;
typedef  scalar_t__ u32 ;
struct ath10k_pci {scalar_t__ mem_len; scalar_t__ mem; } ;
struct ath10k {int dummy; } ;

/* Variables and functions */
 struct ath10k_pci* ath10k_pci_priv (struct ath10k*) ; 
 int /*<<< orphan*/  ath10k_pci_sleep (struct ath10k*) ; 
 int ath10k_pci_wake (struct ath10k*) ; 
 int /*<<< orphan*/  ath10k_warn (struct ath10k*,char*,scalar_t__,int,...) ; 
 scalar_t__ ioread32 (scalar_t__) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static u32 ath10k_bus_pci_read32(struct ath10k *ar, u32 offset)
{
	struct ath10k_pci *ar_pci = ath10k_pci_priv(ar);
	u32 val;
	int ret;

	if (unlikely(offset + sizeof(val) > ar_pci->mem_len)) {
		ath10k_warn(ar, "refusing to read mmio out of bounds at 0x%08x - 0x%08zx (max 0x%08zx)\n",
			    offset, offset + sizeof(val), ar_pci->mem_len);
		return 0;
	}

	ret = ath10k_pci_wake(ar);
	if (ret) {
		ath10k_warn(ar, "failed to wake target for read32 at 0x%08x: %d\n",
			    offset, ret);
		return 0xffffffff;
	}

	val = ioread32(ar_pci->mem + offset);
	ath10k_pci_sleep(ar);

	return val;
}