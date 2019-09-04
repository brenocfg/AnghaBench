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
struct TYPE_2__ {int /*<<< orphan*/  (* set_pll ) (struct fb_info*,struct pll_timing*,int /*<<< orphan*/ ) ;} ;
struct sstfb_par {TYPE_1__ dac_sw; struct pci_dev* dev; } ;
struct pll_timing {int dummy; } ;
struct pci_dev {int dummy; } ;
struct fb_info {struct sstfb_par* par; } ;

/* Variables and functions */
 int DIS_VGA_PASSTHROUGH ; 
 int EN_BLANKING ; 
 int EN_DRAM_REFRESH ; 
 int /*<<< orphan*/  FBIINIT0 ; 
 int /*<<< orphan*/  FBIINIT1 ; 
 int /*<<< orphan*/  FBIINIT2 ; 
 int FBI_RESET ; 
 int FIFO_RESET ; 
 int /*<<< orphan*/  GFX_CLOCK ; 
 int PCI_EN_INIT_WR ; 
 int /*<<< orphan*/  PCI_INIT_ENABLE ; 
 int PCI_REMAP_DAC ; 
 int /*<<< orphan*/  PCI_VCLK_DISABLE ; 
 int VIDEO_RESET ; 
 int /*<<< orphan*/  pci_write_config_dword (struct pci_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sst_calc_pll (int,int*,struct pll_timing*) ; 
 int /*<<< orphan*/  sst_set_bits (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sst_unset_bits (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sst_wait_idle () ; 
 int /*<<< orphan*/  stub1 (struct fb_info*,struct pll_timing*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sst_shutdown(struct fb_info *info)
{
	struct sstfb_par *par = info->par;
	struct pci_dev *dev = par->dev;
	struct pll_timing gfx_timings;
	int Fout;

	/* reset video, gfx, fifo, disable dram + remap fbiinit2/3 */
	pci_write_config_dword(dev, PCI_INIT_ENABLE, PCI_EN_INIT_WR);
	sst_set_bits(FBIINIT1, VIDEO_RESET | EN_BLANKING);
	sst_unset_bits(FBIINIT2, EN_DRAM_REFRESH);
	sst_set_bits(FBIINIT0, FBI_RESET | FIFO_RESET);
	sst_wait_idle();
	pci_write_config_dword(dev, PCI_INIT_ENABLE,
	                       PCI_EN_INIT_WR | PCI_REMAP_DAC);
	/* set 20Mhz gfx clock */
	sst_calc_pll(20000, &Fout, &gfx_timings);
	par->dac_sw.set_pll(info, &gfx_timings, GFX_CLOCK);
	/* TODO maybe shutdown the dac, vrefresh and so on... */
	pci_write_config_dword(dev, PCI_INIT_ENABLE,
	                       PCI_EN_INIT_WR);
	sst_unset_bits(FBIINIT0, FBI_RESET | FIFO_RESET | DIS_VGA_PASSTHROUGH);
	pci_write_config_dword(dev, PCI_VCLK_DISABLE,0);
	/* maybe keep fbiinit* and PCI_INIT_enable in the fb_info struct
	 * from start ? */
	pci_write_config_dword(dev, PCI_INIT_ENABLE, 0);

}