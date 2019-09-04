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
struct snd_card {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_set_drvdata (struct device*,struct snd_card*) ; 
 int /*<<< orphan*/  snd_card_free (struct snd_card*) ; 
 int snd_cmi8330_card_new (struct device*,unsigned int,struct snd_card**) ; 
 int snd_cmi8330_probe (struct snd_card*,unsigned int) ; 

__attribute__((used)) static int snd_cmi8330_isa_probe(struct device *pdev,
				 unsigned int dev)
{
	struct snd_card *card;
	int err;

	err = snd_cmi8330_card_new(pdev, dev, &card);
	if (err < 0)
		return err;
	if ((err = snd_cmi8330_probe(card, dev)) < 0) {
		snd_card_free(card);
		return err;
	}
	dev_set_drvdata(pdev, card);
	return 0;
}