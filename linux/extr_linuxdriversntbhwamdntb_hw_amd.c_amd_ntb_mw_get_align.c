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
struct ntb_dev {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  pdev; } ;
struct amd_ntb_dev {TYPE_1__ ntb; } ;
typedef  int resource_size_t ;

/* Variables and functions */
 int EINVAL ; 
 int NTB_DEF_PEER_IDX ; 
 int SZ_4K ; 
 int ndev_mw_to_bar (struct amd_ntb_dev*,int) ; 
 struct amd_ntb_dev* ntb_ndev (struct ntb_dev*) ; 
 int pci_resource_len (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int amd_ntb_mw_get_align(struct ntb_dev *ntb, int pidx, int idx,
				resource_size_t *addr_align,
				resource_size_t *size_align,
				resource_size_t *size_max)
{
	struct amd_ntb_dev *ndev = ntb_ndev(ntb);
	int bar;

	if (pidx != NTB_DEF_PEER_IDX)
		return -EINVAL;

	bar = ndev_mw_to_bar(ndev, idx);
	if (bar < 0)
		return bar;

	if (addr_align)
		*addr_align = SZ_4K;

	if (size_align)
		*size_align = 1;

	if (size_max)
		*size_max = pci_resource_len(ndev->ntb.pdev, bar);

	return 0;
}