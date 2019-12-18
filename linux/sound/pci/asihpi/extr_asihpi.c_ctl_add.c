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
struct snd_kcontrol_new {int /*<<< orphan*/  index; int /*<<< orphan*/  name; } ;
struct snd_card_asihpi {TYPE_1__* pci; } ;
struct snd_card {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ mixer_dump ; 
 int snd_ctl_add (struct snd_card*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_ctl_new1 (struct snd_kcontrol_new*,struct snd_card_asihpi*) ; 

__attribute__((used)) static inline int ctl_add(struct snd_card *card, struct snd_kcontrol_new *ctl,
				struct snd_card_asihpi *asihpi)
{
	int err;

	err = snd_ctl_add(card, snd_ctl_new1(ctl, asihpi));
	if (err < 0)
		return err;
	else if (mixer_dump)
		dev_info(&asihpi->pci->dev, "added %s(%d)\n", ctl->name, ctl->index);

	return 0;
}