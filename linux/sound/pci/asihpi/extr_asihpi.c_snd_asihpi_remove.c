#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct snd_card_asihpi {int /*<<< orphan*/  t; } ;
struct pci_dev {int dummy; } ;
struct hpi_adapter {TYPE_2__* snd_card; TYPE_1__* adapter; int /*<<< orphan*/ * interrupt_callback; scalar_t__ interrupt_mode; } ;
struct TYPE_4__ {struct snd_card_asihpi* private_data; } ;
struct TYPE_3__ {int /*<<< orphan*/  index; } ;

/* Variables and functions */
 int /*<<< orphan*/  HPI_ADAPTER_PROPERTY_IRQ_RATE ; 
 int /*<<< orphan*/  asihpi_adapter_remove (struct pci_dev*) ; 
 int /*<<< orphan*/  hpi_adapter_set_property (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hpi_handle_error (int /*<<< orphan*/ ) ; 
 struct hpi_adapter* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  snd_card_free (TYPE_2__*) ; 
 int /*<<< orphan*/  tasklet_kill (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void snd_asihpi_remove(struct pci_dev *pci_dev)
{
	struct hpi_adapter *hpi = pci_get_drvdata(pci_dev);
	struct snd_card_asihpi *asihpi = hpi->snd_card->private_data;

	/* Stop interrupts */
	if (hpi->interrupt_mode) {
		hpi->interrupt_callback = NULL;
		hpi_handle_error(hpi_adapter_set_property(hpi->adapter->index,
			HPI_ADAPTER_PROPERTY_IRQ_RATE, 0, 0));
		tasklet_kill(&asihpi->t);
	}

	snd_card_free(hpi->snd_card);
	hpi->snd_card = NULL;
	asihpi_adapter_remove(pci_dev);
}