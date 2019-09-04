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
typedef  int /*<<< orphan*/  u32 ;
struct ath10k {int dummy; } ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int /*<<< orphan*/  __cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int ath10k_pci_diag_write_mem (struct ath10k*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int ath10k_pci_diag_write32(struct ath10k *ar, u32 address, u32 value)
{
	__le32 val = __cpu_to_le32(value);

	return ath10k_pci_diag_write_mem(ar, address, &val, sizeof(val));
}