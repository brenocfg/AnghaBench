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
 int ath10k_pci_diag_read32 (struct ath10k*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int ath10k_pci_diag_read_mem (struct ath10k*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath10k_warn (struct ath10k*,char*,int /*<<< orphan*/ ,int,...) ; 
 int /*<<< orphan*/  host_interest_item_address (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __ath10k_pci_diag_read_hi(struct ath10k *ar, void *dest,
				     u32 src, u32 len)
{
	u32 host_addr, addr;
	int ret;

	host_addr = host_interest_item_address(src);

	ret = ath10k_pci_diag_read32(ar, host_addr, &addr);
	if (ret != 0) {
		ath10k_warn(ar, "failed to get memcpy hi address for firmware address %d: %d\n",
			    src, ret);
		return ret;
	}

	ret = ath10k_pci_diag_read_mem(ar, addr, dest, len);
	if (ret != 0) {
		ath10k_warn(ar, "failed to memcpy firmware memory from %d (%d B): %d\n",
			    addr, len, ret);
		return ret;
	}

	return 0;
}