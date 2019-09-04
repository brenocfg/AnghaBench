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
struct brcmf_pciedev_info {scalar_t__ state; int /*<<< orphan*/  (* write_ptr ) (struct brcmf_pciedev_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct brcmf_commonring {int /*<<< orphan*/  w_ptr; int /*<<< orphan*/  r_ptr; } ;
struct brcmf_pcie_ringbuf {int /*<<< orphan*/  w_idx_addr; int /*<<< orphan*/  id; struct brcmf_commonring commonring; struct brcmf_pciedev_info* devinfo; } ;

/* Variables and functions */
 scalar_t__ BRCMFMAC_PCIE_STATE_UP ; 
 int EIO ; 
 int /*<<< orphan*/  PCIE ; 
 int /*<<< orphan*/  brcmf_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct brcmf_pciedev_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int brcmf_pcie_ring_mb_write_wptr(void *ctx)
{
	struct brcmf_pcie_ringbuf *ring = (struct brcmf_pcie_ringbuf *)ctx;
	struct brcmf_pciedev_info *devinfo = ring->devinfo;
	struct brcmf_commonring *commonring = &ring->commonring;

	if (devinfo->state != BRCMFMAC_PCIE_STATE_UP)
		return -EIO;

	brcmf_dbg(PCIE, "W w_ptr %d (%d), ring %d\n", commonring->w_ptr,
		  commonring->r_ptr, ring->id);

	devinfo->write_ptr(devinfo, ring->w_idx_addr, commonring->w_ptr);

	return 0;
}