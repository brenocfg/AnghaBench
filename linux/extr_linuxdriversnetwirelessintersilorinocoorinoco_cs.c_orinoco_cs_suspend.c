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
struct pcmcia_device {struct orinoco_private* priv; } ;
struct orinoco_private {struct orinoco_pccard* card; } ;
struct orinoco_pccard {int /*<<< orphan*/  hard_reset_in_progress; } ;

/* Variables and functions */
 int /*<<< orphan*/  orinoco_down (struct orinoco_private*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int orinoco_cs_suspend(struct pcmcia_device *link)
{
	struct orinoco_private *priv = link->priv;
	struct orinoco_pccard *card = priv->card;

	/* This is probably racy, but I can't think of
	   a better way, short of rewriting the PCMCIA
	   layer to not suck :-( */
	if (!test_bit(0, &card->hard_reset_in_progress))
		orinoco_down(priv);

	return 0;
}