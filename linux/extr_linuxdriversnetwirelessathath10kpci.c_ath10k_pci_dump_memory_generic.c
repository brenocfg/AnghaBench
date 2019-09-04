#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_2__ {scalar_t__ size; } ;
struct ath10k_mem_region {int len; int /*<<< orphan*/  name; int /*<<< orphan*/  start; TYPE_1__ section_table; } ;
struct ath10k {int dummy; } ;

/* Variables and functions */
 int ath10k_pci_diag_read_mem (struct ath10k*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int ath10k_pci_dump_memory_section (struct ath10k*,struct ath10k_mem_region const*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ath10k_warn (struct ath10k*,char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ath10k_pci_dump_memory_generic(struct ath10k *ar,
					  const struct ath10k_mem_region *current_region,
					  u8 *buf)
{
	int ret;

	if (current_region->section_table.size > 0)
		/* Copy each section individually. */
		return ath10k_pci_dump_memory_section(ar,
						      current_region,
						      buf,
						      current_region->len);

	/* No individiual memory sections defined so we can
	 * copy the entire memory region.
	 */
	ret = ath10k_pci_diag_read_mem(ar,
				       current_region->start,
				       buf,
				       current_region->len);
	if (ret) {
		ath10k_warn(ar, "failed to copy ramdump region %s: %d\n",
			    current_region->name, ret);
		return ret;
	}

	return current_region->len;
}