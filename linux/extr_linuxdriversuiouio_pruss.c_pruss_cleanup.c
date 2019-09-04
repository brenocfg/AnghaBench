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
struct uio_pruss_dev {int /*<<< orphan*/  pruss_clk; struct uio_pruss_dev* info; scalar_t__ sram_vaddr; int /*<<< orphan*/  sram_pool; int /*<<< orphan*/  ddr_paddr; scalar_t__ ddr_vaddr; int /*<<< orphan*/  prussio_vaddr; struct uio_pruss_dev* name; } ;
struct uio_info {int /*<<< orphan*/  pruss_clk; struct uio_info* info; scalar_t__ sram_vaddr; int /*<<< orphan*/  sram_pool; int /*<<< orphan*/  ddr_paddr; scalar_t__ ddr_vaddr; int /*<<< orphan*/  prussio_vaddr; struct uio_info* name; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int MAX_PRUSS_EVT ; 
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_free_coherent (struct device*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  extram_pool_sz ; 
 int /*<<< orphan*/  gen_pool_free (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct uio_pruss_dev*) ; 
 int /*<<< orphan*/  sram_pool_sz ; 
 int /*<<< orphan*/  uio_unregister_device (struct uio_pruss_dev*) ; 

__attribute__((used)) static void pruss_cleanup(struct device *dev, struct uio_pruss_dev *gdev)
{
	int cnt;
	struct uio_info *p = gdev->info;

	for (cnt = 0; cnt < MAX_PRUSS_EVT; cnt++, p++) {
		uio_unregister_device(p);
		kfree(p->name);
	}
	iounmap(gdev->prussio_vaddr);
	if (gdev->ddr_vaddr) {
		dma_free_coherent(dev, extram_pool_sz, gdev->ddr_vaddr,
			gdev->ddr_paddr);
	}
	if (gdev->sram_vaddr)
		gen_pool_free(gdev->sram_pool,
			      gdev->sram_vaddr,
			      sram_pool_sz);
	kfree(gdev->info);
	clk_disable(gdev->pruss_clk);
	clk_put(gdev->pruss_clk);
	kfree(gdev);
}