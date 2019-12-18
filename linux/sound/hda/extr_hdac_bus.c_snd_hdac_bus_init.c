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
struct hdac_bus_ops {int dummy; } ;
struct hdac_bus {int irq; int /*<<< orphan*/  hlink_list; int /*<<< orphan*/  lock; int /*<<< orphan*/  cmd_mutex; int /*<<< orphan*/  reg_lock; int /*<<< orphan*/  unsol_work; int /*<<< orphan*/  codec_list; int /*<<< orphan*/  stream_list; int /*<<< orphan*/  dma_type; struct hdac_bus_ops const* ops; struct device* dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SNDRV_DMA_TYPE_DEV ; 
 struct hdac_bus_ops const default_ops ; 
 int /*<<< orphan*/  memset (struct hdac_bus*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_hdac_bus_process_unsol_events ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

int snd_hdac_bus_init(struct hdac_bus *bus, struct device *dev,
		      const struct hdac_bus_ops *ops)
{
	memset(bus, 0, sizeof(*bus));
	bus->dev = dev;
	if (ops)
		bus->ops = ops;
	else
		bus->ops = &default_ops;
	bus->dma_type = SNDRV_DMA_TYPE_DEV;
	INIT_LIST_HEAD(&bus->stream_list);
	INIT_LIST_HEAD(&bus->codec_list);
	INIT_WORK(&bus->unsol_work, snd_hdac_bus_process_unsol_events);
	spin_lock_init(&bus->reg_lock);
	mutex_init(&bus->cmd_mutex);
	mutex_init(&bus->lock);
	INIT_LIST_HEAD(&bus->hlink_list);
	bus->irq = -1;
	return 0;
}