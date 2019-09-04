#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct switchtec_ntb {TYPE_2__* stdev; TYPE_1__* peer_shared; } ;
struct ntb_dev {int /*<<< orphan*/  pdev; } ;
typedef  scalar_t__ phys_addr_t ;
struct TYPE_4__ {scalar_t__ mmio; } ;
struct TYPE_3__ {int /*<<< orphan*/ * spad; } ;

/* Variables and functions */
 int EINVAL ; 
 int NTB_DEF_PEER_IDX ; 
 struct switchtec_ntb* ntb_sndev (struct ntb_dev*) ; 
 scalar_t__ pci_resource_start (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int switchtec_ntb_peer_spad_addr(struct ntb_dev *ntb, int pidx,
					int sidx, phys_addr_t *spad_addr)
{
	struct switchtec_ntb *sndev = ntb_sndev(ntb);
	unsigned long offset;

	if (pidx != NTB_DEF_PEER_IDX)
		return -EINVAL;

	offset = (unsigned long)&sndev->peer_shared->spad[sidx] -
		(unsigned long)sndev->stdev->mmio;

	if (spad_addr)
		*spad_addr = pci_resource_start(ntb->pdev, 0) + offset;

	return 0;
}