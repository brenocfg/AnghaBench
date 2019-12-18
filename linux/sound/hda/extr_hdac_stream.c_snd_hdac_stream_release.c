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
struct hdac_stream {int /*<<< orphan*/ * substream; scalar_t__ running; scalar_t__ opened; struct hdac_bus* bus; } ;
struct hdac_bus {int /*<<< orphan*/  reg_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

void snd_hdac_stream_release(struct hdac_stream *azx_dev)
{
	struct hdac_bus *bus = azx_dev->bus;

	spin_lock_irq(&bus->reg_lock);
	azx_dev->opened = 0;
	azx_dev->running = 0;
	azx_dev->substream = NULL;
	spin_unlock_irq(&bus->reg_lock);
}