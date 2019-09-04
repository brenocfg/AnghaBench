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
struct TYPE_2__ {int /*<<< orphan*/  opened; struct hdac_bus* bus; } ;
struct hdac_ext_stream {int /*<<< orphan*/ * link_substream; int /*<<< orphan*/  link_locked; TYPE_1__ hstream; int /*<<< orphan*/  decoupled; } ;
struct hdac_bus {int /*<<< orphan*/  dev; int /*<<< orphan*/  reg_lock; } ;

/* Variables and functions */
#define  HDAC_EXT_STREAM_TYPE_COUPLED 130 
#define  HDAC_EXT_STREAM_TYPE_HOST 129 
#define  HDAC_EXT_STREAM_TYPE_LINK 128 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  snd_hdac_ext_stream_decouple (struct hdac_bus*,struct hdac_ext_stream*,int) ; 
 int /*<<< orphan*/  snd_hdac_stream_release (TYPE_1__*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

void snd_hdac_ext_stream_release(struct hdac_ext_stream *stream, int type)
{
	struct hdac_bus *bus = stream->hstream.bus;

	switch (type) {
	case HDAC_EXT_STREAM_TYPE_COUPLED:
		snd_hdac_stream_release(&stream->hstream);
		break;

	case HDAC_EXT_STREAM_TYPE_HOST:
		if (stream->decoupled && !stream->link_locked)
			snd_hdac_ext_stream_decouple(bus, stream, false);
		snd_hdac_stream_release(&stream->hstream);
		break;

	case HDAC_EXT_STREAM_TYPE_LINK:
		if (stream->decoupled && !stream->hstream.opened)
			snd_hdac_ext_stream_decouple(bus, stream, false);
		spin_lock_irq(&bus->reg_lock);
		stream->link_locked = 0;
		stream->link_substream = NULL;
		spin_unlock_irq(&bus->reg_lock);
		break;

	default:
		dev_dbg(bus->dev, "Invalid type %d\n", type);
	}

}