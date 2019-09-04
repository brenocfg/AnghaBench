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
struct mtpav {int /*<<< orphan*/  spinlock; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  snd_mtpav_read_bytes (struct mtpav*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t snd_mtpav_irqh(int irq, void *dev_id)
{
	struct mtpav *mcard = dev_id;

	spin_lock(&mcard->spinlock);
	snd_mtpav_read_bytes(mcard);
	spin_unlock(&mcard->spinlock);
	return IRQ_HANDLED;
}