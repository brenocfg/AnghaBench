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
struct pci_dev {int dummy; } ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 int pci_user_write_config_byte (struct pci_dev*,int,int /*<<< orphan*/ ) ; 
 int pci_user_write_config_dword (struct pci_dev*,int,int /*<<< orphan*/ ) ; 
 int pci_user_write_config_word (struct pci_dev*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vfio_user_config_write(struct pci_dev *pdev, int offset,
				  __le32 val, int count)
{
	int ret = -EINVAL;
	u32 tmp_val = le32_to_cpu(val);

	switch (count) {
	case 1:
		ret = pci_user_write_config_byte(pdev, offset, tmp_val);
		break;
	case 2:
		ret = pci_user_write_config_word(pdev, offset, tmp_val);
		break;
	case 4:
		ret = pci_user_write_config_dword(pdev, offset, tmp_val);
		break;
	}

	return ret;
}