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
struct hdac_stream {int sd_int_sta_mask; int index; int direction; int stream_tag; int /*<<< orphan*/  list; scalar_t__ sd_addr; struct hdac_bus* bus; } ;
struct hdac_bus {int /*<<< orphan*/  stream_list; scalar_t__ remap_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_hdac_dsp_lock_init (struct hdac_stream*) ; 

void snd_hdac_stream_init(struct hdac_bus *bus, struct hdac_stream *azx_dev,
			  int idx, int direction, int tag)
{
	azx_dev->bus = bus;
	/* offset: SDI0=0x80, SDI1=0xa0, ... SDO3=0x160 */
	azx_dev->sd_addr = bus->remap_addr + (0x20 * idx + 0x80);
	/* int mask: SDI0=0x01, SDI1=0x02, ... SDO3=0x80 */
	azx_dev->sd_int_sta_mask = 1 << idx;
	azx_dev->index = idx;
	azx_dev->direction = direction;
	azx_dev->stream_tag = tag;
	snd_hdac_dsp_lock_init(azx_dev);
	list_add_tail(&azx_dev->list, &bus->stream_list);
}