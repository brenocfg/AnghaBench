#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/ * area; } ;
struct mixart_mgr {unsigned int num_cards; scalar_t__ irq; TYPE_4__* pci; TYPE_3__ bufferinfo; TYPE_3__ flowinfo; TYPE_2__* mem; scalar_t__ dsp_loaded; TYPE_1__** chip; } ;
struct TYPE_9__ {int /*<<< orphan*/  dev; } ;
struct TYPE_7__ {int /*<<< orphan*/  virt; } ;
struct TYPE_6__ {int /*<<< orphan*/  card; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  free_irq (scalar_t__,struct mixart_mgr*) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct mixart_mgr*) ; 
 int /*<<< orphan*/  pci_disable_device (TYPE_4__*) ; 
 int /*<<< orphan*/  pci_release_regions (TYPE_4__*) ; 
 int /*<<< orphan*/  snd_card_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_dma_free_pages (TYPE_3__*) ; 
 int /*<<< orphan*/  snd_mixart_exit_mailbox (struct mixart_mgr*) ; 
 int /*<<< orphan*/  snd_mixart_reset_board (struct mixart_mgr*) ; 

__attribute__((used)) static int snd_mixart_free(struct mixart_mgr *mgr)
{
	unsigned int i;

	for (i = 0; i < mgr->num_cards; i++) {
		if (mgr->chip[i])
			snd_card_free(mgr->chip[i]->card);
	}

	/* stop mailbox */
	snd_mixart_exit_mailbox(mgr);

	/* release irq  */
	if (mgr->irq >= 0)
		free_irq(mgr->irq, mgr);

	/* reset board if some firmware was loaded */
	if(mgr->dsp_loaded) {
		snd_mixart_reset_board(mgr);
		dev_dbg(&mgr->pci->dev, "reset miXart !\n");
	}

	/* release the i/o ports */
	for (i = 0; i < 2; ++i)
		iounmap(mgr->mem[i].virt);

	pci_release_regions(mgr->pci);

	/* free flowarray */
	if(mgr->flowinfo.area) {
		snd_dma_free_pages(&mgr->flowinfo);
		mgr->flowinfo.area = NULL;
	}
	/* free bufferarray */
	if(mgr->bufferinfo.area) {
		snd_dma_free_pages(&mgr->bufferinfo);
		mgr->bufferinfo.area = NULL;
	}

	pci_disable_device(mgr->pci);
	kfree(mgr);
	return 0;
}