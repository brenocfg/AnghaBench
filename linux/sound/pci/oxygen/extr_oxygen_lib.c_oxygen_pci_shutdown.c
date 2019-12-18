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
struct snd_card {struct oxygen* private_data; } ;
struct pci_dev {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* cleanup ) (struct oxygen*) ;} ;
struct oxygen {TYPE_1__ model; } ;

/* Variables and functions */
 int /*<<< orphan*/  oxygen_shutdown (struct oxygen*) ; 
 struct snd_card* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  stub1 (struct oxygen*) ; 

void oxygen_pci_shutdown(struct pci_dev *pci)
{
	struct snd_card *card = pci_get_drvdata(pci);
	struct oxygen *chip = card->private_data;

	oxygen_shutdown(chip);
	chip->model.cleanup(chip);
}