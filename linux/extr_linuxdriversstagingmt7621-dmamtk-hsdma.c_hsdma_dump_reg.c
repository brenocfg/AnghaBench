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
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct mtk_hsdam_engine {TYPE_1__ ddev; } ;

/* Variables and functions */
 int /*<<< orphan*/  HSDMA_REG_DELAY_INT ; 
 int /*<<< orphan*/  HSDMA_REG_GLO_CFG ; 
 int /*<<< orphan*/  HSDMA_REG_INFO ; 
 int /*<<< orphan*/  HSDMA_REG_INT_MASK ; 
 int /*<<< orphan*/  HSDMA_REG_INT_STATUS ; 
 int /*<<< orphan*/  HSDMA_REG_RX_BASE ; 
 int /*<<< orphan*/  HSDMA_REG_RX_CNT ; 
 int /*<<< orphan*/  HSDMA_REG_RX_CRX ; 
 int /*<<< orphan*/  HSDMA_REG_RX_DRX ; 
 int /*<<< orphan*/  HSDMA_REG_TX_BASE ; 
 int /*<<< orphan*/  HSDMA_REG_TX_CNT ; 
 int /*<<< orphan*/  HSDMA_REG_TX_CTX ; 
 int /*<<< orphan*/  HSDMA_REG_TX_DTX ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  mtk_hsdma_read (struct mtk_hsdam_engine*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hsdma_dump_reg(struct mtk_hsdam_engine *hsdma)
{
	dev_dbg(hsdma->ddev.dev, "tbase %08x, tcnt %08x, " \
			"tctx %08x, tdtx: %08x, rbase %08x, " \
			"rcnt %08x, rctx %08x, rdtx %08x\n",
			mtk_hsdma_read(hsdma, HSDMA_REG_TX_BASE),
			mtk_hsdma_read(hsdma, HSDMA_REG_TX_CNT),
			mtk_hsdma_read(hsdma, HSDMA_REG_TX_CTX),
			mtk_hsdma_read(hsdma, HSDMA_REG_TX_DTX),
			mtk_hsdma_read(hsdma, HSDMA_REG_RX_BASE),
			mtk_hsdma_read(hsdma, HSDMA_REG_RX_CNT),
			mtk_hsdma_read(hsdma, HSDMA_REG_RX_CRX),
			mtk_hsdma_read(hsdma, HSDMA_REG_RX_DRX));

	dev_dbg(hsdma->ddev.dev, "info %08x, glo %08x, delay %08x, " \
			"intr_stat %08x, intr_mask %08x\n",
			mtk_hsdma_read(hsdma, HSDMA_REG_INFO),
			mtk_hsdma_read(hsdma, HSDMA_REG_GLO_CFG),
			mtk_hsdma_read(hsdma, HSDMA_REG_DELAY_INT),
			mtk_hsdma_read(hsdma, HSDMA_REG_INT_STATUS),
			mtk_hsdma_read(hsdma, HSDMA_REG_INT_MASK));
}