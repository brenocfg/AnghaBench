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
struct brcmf_pciedev_info {int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  brcmf_pcie_buscore_prep_addr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brcmf_pcie_read_reg32 (struct brcmf_pciedev_info*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 brcmf_pcie_buscore_read32(void *ctx, u32 addr)
{
	struct brcmf_pciedev_info *devinfo = (struct brcmf_pciedev_info *)ctx;

	addr = brcmf_pcie_buscore_prep_addr(devinfo->pdev, addr);
	return brcmf_pcie_read_reg32(devinfo, addr);
}