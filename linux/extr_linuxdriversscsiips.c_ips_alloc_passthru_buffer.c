#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char* ioctl_data; int ioctl_len; int /*<<< orphan*/  ioctl_busaddr; int /*<<< orphan*/  pcidev; } ;
typedef  TYPE_1__ ips_ha_t ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 void* pci_alloc_consistent (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_free_consistent (int /*<<< orphan*/ ,int,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ips_alloc_passthru_buffer(ips_ha_t * ha, int length)
{
	void *bigger_buf;
	dma_addr_t dma_busaddr;

	if (ha->ioctl_data && length <= ha->ioctl_len)
		return 0;
	/* there is no buffer or it's not big enough, allocate a new one */
	bigger_buf = pci_alloc_consistent(ha->pcidev, length, &dma_busaddr);
	if (bigger_buf) {
		/* free the old memory */
		pci_free_consistent(ha->pcidev, ha->ioctl_len, ha->ioctl_data,
				    ha->ioctl_busaddr);
		/* use the new memory */
		ha->ioctl_data = (char *) bigger_buf;
		ha->ioctl_len = length;
		ha->ioctl_busaddr = dma_busaddr;
	} else {
		return -1;
	}
	return 0;
}