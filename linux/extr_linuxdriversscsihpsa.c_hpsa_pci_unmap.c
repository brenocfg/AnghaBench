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
struct pci_dev {int dummy; } ;
struct CommandList {TYPE_1__* SG; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_2__ {int /*<<< orphan*/  Len; int /*<<< orphan*/  Addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_unmap_single (struct pci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void hpsa_pci_unmap(struct pci_dev *pdev,
	struct CommandList *c, int sg_used, int data_direction)
{
	int i;

	for (i = 0; i < sg_used; i++)
		pci_unmap_single(pdev, (dma_addr_t) le64_to_cpu(c->SG[i].Addr),
				le32_to_cpu(c->SG[i].Len),
				data_direction);
}