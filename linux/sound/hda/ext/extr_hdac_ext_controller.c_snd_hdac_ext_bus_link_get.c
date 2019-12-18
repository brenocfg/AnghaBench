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
struct hdac_ext_link {int ref_count; int /*<<< orphan*/  ml_addr; } ;
struct hdac_bus {int cmd_dma_state; int /*<<< orphan*/  lock; int /*<<< orphan*/  codec_mask; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  AZX_REG_ML_LOSIDV ; 
 int /*<<< orphan*/  ML_LOSIDV_STREAM_MASK ; 
 int /*<<< orphan*/  STATESTS ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_hdac_bus_init_cmd_io (struct hdac_bus*) ; 
 int /*<<< orphan*/  snd_hdac_chip_readw (struct hdac_bus*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_hdac_chip_writew (struct hdac_bus*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int snd_hdac_ext_bus_link_power_up (struct hdac_ext_link*) ; 
 int /*<<< orphan*/  snd_hdac_updatew (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

int snd_hdac_ext_bus_link_get(struct hdac_bus *bus,
				struct hdac_ext_link *link)
{
	int ret = 0;

	mutex_lock(&bus->lock);

	/*
	 * if we move from 0 to 1, count will be 1 so power up this link
	 * as well, also check the dma status and trigger that
	 */
	if (++link->ref_count == 1) {
		if (!bus->cmd_dma_state) {
			snd_hdac_bus_init_cmd_io(bus);
			bus->cmd_dma_state = true;
		}

		ret = snd_hdac_ext_bus_link_power_up(link);

		/*
		 * clear the register to invalidate all the output streams
		 */
		snd_hdac_updatew(link->ml_addr, AZX_REG_ML_LOSIDV,
				 ML_LOSIDV_STREAM_MASK, 0);
		/*
		 *  wait for 521usec for codec to report status
		 *  HDA spec section 4.3 - Codec Discovery
		 */
		udelay(521);
		bus->codec_mask = snd_hdac_chip_readw(bus, STATESTS);
		dev_dbg(bus->dev, "codec_mask = 0x%lx\n", bus->codec_mask);
		snd_hdac_chip_writew(bus, STATESTS, bus->codec_mask);
	}

	mutex_unlock(&bus->lock);
	return ret;
}