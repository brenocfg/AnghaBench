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
struct platform_device {int /*<<< orphan*/ * resource; } ;
struct esp {int /*<<< orphan*/  dmarev; int /*<<< orphan*/  dma_regs; struct platform_device* dma; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_CSR ; 
 int DMA_DEVICE_ID ; 
#define  DMA_ESCV1 133 
#define  DMA_VERHME 132 
#define  DMA_VERS0 131 
#define  DMA_VERS1 130 
#define  DMA_VERS2 129 
#define  DMA_VERSPLUS 128 
 int ENOMEM ; 
 int dma_read32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dvmaesc1 ; 
 int /*<<< orphan*/  dvmahme ; 
 int /*<<< orphan*/  dvmarev0 ; 
 int /*<<< orphan*/  dvmarev1 ; 
 int /*<<< orphan*/  dvmarev2 ; 
 int /*<<< orphan*/  dvmarevplus ; 
 int /*<<< orphan*/  of_ioremap (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  resource_size (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int esp_sbus_setup_dma(struct esp *esp, struct platform_device *dma_of)
{
	esp->dma = dma_of;

	esp->dma_regs = of_ioremap(&dma_of->resource[0], 0,
				   resource_size(&dma_of->resource[0]),
				   "espdma");
	if (!esp->dma_regs)
		return -ENOMEM;

	switch (dma_read32(DMA_CSR) & DMA_DEVICE_ID) {
	case DMA_VERS0:
		esp->dmarev = dvmarev0;
		break;
	case DMA_ESCV1:
		esp->dmarev = dvmaesc1;
		break;
	case DMA_VERS1:
		esp->dmarev = dvmarev1;
		break;
	case DMA_VERS2:
		esp->dmarev = dvmarev2;
		break;
	case DMA_VERHME:
		esp->dmarev = dvmahme;
		break;
	case DMA_VERSPLUS:
		esp->dmarev = dvmarevplus;
		break;
	}

	return 0;

}