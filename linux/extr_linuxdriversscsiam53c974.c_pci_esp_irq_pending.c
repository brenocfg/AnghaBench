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
struct pci_esp_priv {int dma_status; } ;
struct esp {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_DMA_STATUS ; 
 int ESP_DMA_STAT_ABORT ; 
 int ESP_DMA_STAT_DONE ; 
 int ESP_DMA_STAT_ERROR ; 
 int ESP_DMA_STAT_SCSIINT ; 
 int /*<<< orphan*/  esp_dma_log (char*,int) ; 
 struct pci_esp_priv* pci_esp_get_priv (struct esp*) ; 
 int pci_esp_read8 (struct esp*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pci_esp_irq_pending(struct esp *esp)
{
	struct pci_esp_priv *pep = pci_esp_get_priv(esp);

	pep->dma_status = pci_esp_read8(esp, ESP_DMA_STATUS);
	esp_dma_log("dma intr dreg[%02x]\n", pep->dma_status);

	if (pep->dma_status & (ESP_DMA_STAT_ERROR |
			       ESP_DMA_STAT_ABORT |
			       ESP_DMA_STAT_DONE |
			       ESP_DMA_STAT_SCSIINT))
		return 1;

	return 0;
}