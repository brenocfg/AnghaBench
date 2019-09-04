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
struct snic_sg_desc {scalar_t__ addr; int /*<<< orphan*/  len; } ;
struct snic_req_info {int dummy; } ;
struct snic {int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_DMA_FROMDEVICE ; 
 int /*<<< orphan*/  SNIC_BUG_ON (int) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le64_to_cpu (scalar_t__) ; 
 int /*<<< orphan*/  pci_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct snic_sg_desc* req_to_sgl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rqi_to_req (struct snic_req_info*) ; 

void
snic_pci_unmap_rsp_buf(struct snic *snic, struct snic_req_info *rqi)
{
	struct snic_sg_desc *sgd;

	sgd = req_to_sgl(rqi_to_req(rqi));
	SNIC_BUG_ON(sgd[0].addr == 0);
	pci_unmap_single(snic->pdev,
			 le64_to_cpu(sgd[0].addr),
			 le32_to_cpu(sgd[0].len),
			 PCI_DMA_FROMDEVICE);
}