#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/ * area; } ;
struct pcxhr_mgr {unsigned int num_cards; scalar_t__ irq; TYPE_3__* pci; struct pcxhr_mgr* prmh; TYPE_2__ hostport; scalar_t__ dsp_loaded; TYPE_1__** chip; } ;
struct TYPE_7__ {int /*<<< orphan*/  dev; } ;
struct TYPE_5__ {int /*<<< orphan*/  card; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  free_irq (scalar_t__,struct pcxhr_mgr*) ; 
 int /*<<< orphan*/  kfree (struct pcxhr_mgr*) ; 
 int /*<<< orphan*/  pci_disable_device (TYPE_3__*) ; 
 int /*<<< orphan*/  pci_release_regions (TYPE_3__*) ; 
 int /*<<< orphan*/  pcxhr_reset_board (struct pcxhr_mgr*) ; 
 int /*<<< orphan*/  snd_card_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_dma_free_pages (TYPE_2__*) ; 

__attribute__((used)) static int pcxhr_free(struct pcxhr_mgr *mgr)
{
	unsigned int i;

	for (i = 0; i < mgr->num_cards; i++) {
		if (mgr->chip[i])
			snd_card_free(mgr->chip[i]->card);
	}

	/* reset board if some firmware was loaded */
	if(mgr->dsp_loaded) {
		pcxhr_reset_board(mgr);
		dev_dbg(&mgr->pci->dev, "reset pcxhr !\n");
	}

	/* release irq  */
	if (mgr->irq >= 0)
		free_irq(mgr->irq, mgr);

	pci_release_regions(mgr->pci);

	/* free hostport purgebuffer */
	if (mgr->hostport.area) {
		snd_dma_free_pages(&mgr->hostport);
		mgr->hostport.area = NULL;
	}

	kfree(mgr->prmh);

	pci_disable_device(mgr->pci);
	kfree(mgr);
	return 0;
}