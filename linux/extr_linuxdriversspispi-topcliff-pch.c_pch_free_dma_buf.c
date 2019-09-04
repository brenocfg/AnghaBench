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
struct pch_spi_dma_ctrl {scalar_t__ rx_buf_dma; int /*<<< orphan*/  rx_buf_virt; scalar_t__ tx_buf_dma; int /*<<< orphan*/  tx_buf_virt; } ;
struct pch_spi_data {struct pch_spi_dma_ctrl dma; } ;
struct pch_spi_board_data {TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCH_BUF_SIZE ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void pch_free_dma_buf(struct pch_spi_board_data *board_dat,
			     struct pch_spi_data *data)
{
	struct pch_spi_dma_ctrl *dma;

	dma = &data->dma;
	if (dma->tx_buf_dma)
		dma_free_coherent(&board_dat->pdev->dev, PCH_BUF_SIZE,
				  dma->tx_buf_virt, dma->tx_buf_dma);
	if (dma->rx_buf_dma)
		dma_free_coherent(&board_dat->pdev->dev, PCH_BUF_SIZE,
				  dma->rx_buf_virt, dma->rx_buf_dma);
}