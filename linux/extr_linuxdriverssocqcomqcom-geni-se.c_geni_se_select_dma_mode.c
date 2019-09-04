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
typedef  int u32 ;
struct geni_se {scalar_t__ base; } ;

/* Variables and functions */
 int GENI_DMA_MODE_EN ; 
 scalar_t__ SE_DMA_RX_IRQ_CLR ; 
 scalar_t__ SE_DMA_TX_IRQ_CLR ; 
 scalar_t__ SE_GENI_DMA_MODE_EN ; 
 scalar_t__ SE_GENI_M_IRQ_CLEAR ; 
 scalar_t__ SE_GENI_S_IRQ_CLEAR ; 
 scalar_t__ SE_GSI_EVENT_EN ; 
 scalar_t__ SE_IRQ_EN ; 
 int readl_relaxed (scalar_t__) ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

__attribute__((used)) static void geni_se_select_dma_mode(struct geni_se *se)
{
	u32 val;

	writel_relaxed(0, se->base + SE_GSI_EVENT_EN);
	writel_relaxed(0xffffffff, se->base + SE_GENI_M_IRQ_CLEAR);
	writel_relaxed(0xffffffff, se->base + SE_GENI_S_IRQ_CLEAR);
	writel_relaxed(0xffffffff, se->base + SE_DMA_TX_IRQ_CLR);
	writel_relaxed(0xffffffff, se->base + SE_DMA_RX_IRQ_CLR);
	writel_relaxed(0xffffffff, se->base + SE_IRQ_EN);

	val = readl_relaxed(se->base + SE_GENI_DMA_MODE_EN);
	val |= GENI_DMA_MODE_EN;
	writel_relaxed(val, se->base + SE_GENI_DMA_MODE_EN);
}