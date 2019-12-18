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
struct snd_card {struct mtpav* private_data; } ;
struct mtpav {scalar_t__ istimer; scalar_t__ irq; int /*<<< orphan*/  res_port; int /*<<< orphan*/  spinlock; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_irq (scalar_t__,void*) ; 
 int /*<<< orphan*/  release_and_free_resource (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_mtpav_remove_output_timer (struct mtpav*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void snd_mtpav_free(struct snd_card *card)
{
	struct mtpav *crd = card->private_data;
	unsigned long flags;

	spin_lock_irqsave(&crd->spinlock, flags);
	if (crd->istimer > 0)
		snd_mtpav_remove_output_timer(crd);
	spin_unlock_irqrestore(&crd->spinlock, flags);
	if (crd->irq >= 0)
		free_irq(crd->irq, (void *)crd);
	release_and_free_resource(crd->res_port);
}