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
struct brcmf_pciedev_info {scalar_t__ state; int /*<<< orphan*/  (* read_ptr ) (struct brcmf_pciedev_info*,int /*<<< orphan*/ ) ;} ;
struct brcmf_commonring {int /*<<< orphan*/  w_ptr; int /*<<< orphan*/  r_ptr; } ;
struct brcmf_pcie_ringbuf {int /*<<< orphan*/  id; int /*<<< orphan*/  r_idx_addr; struct brcmf_commonring commonring; struct brcmf_pciedev_info* devinfo; } ;

/* Variables and functions */
 scalar_t__ BRCMFMAC_PCIE_STATE_UP ; 
 int EIO ; 
 int /*<<< orphan*/  PCIE ; 
 int /*<<< orphan*/  brcmf_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct brcmf_pciedev_info*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int brcmf_pcie_ring_mb_update_rptr(void *ctx)
{
	struct brcmf_pcie_ringbuf *ring = (struct brcmf_pcie_ringbuf *)ctx;
	struct brcmf_pciedev_info *devinfo = ring->devinfo;
	struct brcmf_commonring *commonring = &ring->commonring;

	if (devinfo->state != BRCMFMAC_PCIE_STATE_UP)
		return -EIO;

	commonring->r_ptr = devinfo->read_ptr(devinfo, ring->r_idx_addr);

	brcmf_dbg(PCIE, "R r_ptr %d (%d), ring %d\n", commonring->r_ptr,
		  commonring->w_ptr, ring->id);

	return 0;
}