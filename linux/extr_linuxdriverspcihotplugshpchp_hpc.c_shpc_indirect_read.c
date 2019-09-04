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
struct pci_dev {int dummy; } ;
struct controller {struct pci_dev* pci_dev; scalar_t__ cap_offset; } ;

/* Variables and functions */
 scalar_t__ DWORD_DATA ; 
 scalar_t__ DWORD_SELECT ; 
 int pci_read_config_dword (struct pci_dev*,scalar_t__,scalar_t__*) ; 
 int pci_write_config_byte (struct pci_dev*,scalar_t__,int) ; 

__attribute__((used)) static inline int shpc_indirect_read(struct controller *ctrl, int index,
				     u32 *value)
{
	int rc;
	u32 cap_offset = ctrl->cap_offset;
	struct pci_dev *pdev = ctrl->pci_dev;

	rc = pci_write_config_byte(pdev, cap_offset + DWORD_SELECT, index);
	if (rc)
		return rc;
	return pci_read_config_dword(pdev, cap_offset + DWORD_DATA, value);
}