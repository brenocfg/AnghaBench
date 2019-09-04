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
typedef  int u8 ;
typedef  int u32 ;

/* Variables and functions */
 int ARRAY_SIZE (int const*) ; 
#define  DMA_TX_DATA_SGL_OVERFLOW 138 
#define  DMA_TX_DIF_APP_ERR 137 
#define  DMA_TX_DIF_CRC_ERR 136 
#define  DMA_TX_DIF_LEN_ALIGN_ERR 135 
#define  DMA_TX_DIF_RPP_ERR 134 
#define  DMA_TX_DIF_SGL_OVERFLOW 133 
 int const DMA_TX_ERR_BASE ; 
 int DMA_TX_ERR_MSK ; 
#define  DMA_TX_RAM_ECC_ERR 132 
#define  DMA_TX_UNEXP_RETRANS_ERR 131 
#define  DMA_TX_UNEXP_XFER_ERR 130 
#define  DMA_TX_XFER_LEN_OVERFLOW 129 
#define  DMA_TX_XFER_OFFSET_ERR 128 

__attribute__((used)) static int parse_dma_tx_err_code_v2_hw(u32 err_msk)
{
	static const u8 dma_tx_err_code_prio[] = {
		DMA_TX_UNEXP_XFER_ERR,
		DMA_TX_UNEXP_RETRANS_ERR,
		DMA_TX_XFER_LEN_OVERFLOW,
		DMA_TX_XFER_OFFSET_ERR,
		DMA_TX_RAM_ECC_ERR,
		DMA_TX_DIF_LEN_ALIGN_ERR,
		DMA_TX_DIF_CRC_ERR,
		DMA_TX_DIF_APP_ERR,
		DMA_TX_DIF_RPP_ERR,
		DMA_TX_DATA_SGL_OVERFLOW,
		DMA_TX_DIF_SGL_OVERFLOW,
	};
	int index, i;

	for (i = 0; i < ARRAY_SIZE(dma_tx_err_code_prio); i++) {
		index = dma_tx_err_code_prio[i] - DMA_TX_ERR_BASE;
		err_msk = err_msk & DMA_TX_ERR_MSK;
		if (err_msk & (1 << index))
			return dma_tx_err_code_prio[i];
	}
	return -1;
}