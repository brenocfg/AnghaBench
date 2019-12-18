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
struct snd_ice1712 {TYPE_1__* card_info; } ;
struct snd_card {struct snd_ice1712* private_data; } ;
struct pci_dev {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* chip_exit ) (struct snd_ice1712*) ;} ;

/* Variables and functions */
 struct snd_card* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  snd_card_free (struct snd_card*) ; 
 int /*<<< orphan*/  stub1 (struct snd_ice1712*) ; 

__attribute__((used)) static void snd_vt1724_remove(struct pci_dev *pci)
{
	struct snd_card *card = pci_get_drvdata(pci);
	struct snd_ice1712 *ice = card->private_data;

	if (ice->card_info && ice->card_info->chip_exit)
		ice->card_info->chip_exit(ice);
	snd_card_free(card);
}