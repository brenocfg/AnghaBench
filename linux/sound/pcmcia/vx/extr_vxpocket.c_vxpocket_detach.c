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
struct vx_core {int /*<<< orphan*/  card; int /*<<< orphan*/  chip_status; } ;
struct snd_vxpocket {int index; } ;
struct pcmcia_device {struct snd_vxpocket* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  VX_STAT_IS_STALE ; 
 int card_alloc ; 
 int /*<<< orphan*/  snd_card_disconnect (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_card_free_when_closed (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vxpocket_release (struct pcmcia_device*) ; 

__attribute__((used)) static void vxpocket_detach(struct pcmcia_device *link)
{
	struct snd_vxpocket *vxp;
	struct vx_core *chip;

	if (! link)
		return;

	vxp = link->priv;
	chip = (struct vx_core *)vxp;
	card_alloc &= ~(1 << vxp->index);

	chip->chip_status |= VX_STAT_IS_STALE; /* to be sure */
	snd_card_disconnect(chip->card);
	vxpocket_release(link);
	snd_card_free_when_closed(chip->card);
}