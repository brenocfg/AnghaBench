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
struct hdac_ext_stream {int /*<<< orphan*/  fifo_addr; } ;
struct hdac_bus {int /*<<< orphan*/  dev; int /*<<< orphan*/  spbcap; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int readl (int /*<<< orphan*/ ) ; 

int snd_hdac_ext_stream_get_spbmaxfifo(struct hdac_bus *bus,
				 struct hdac_ext_stream *stream)
{

	if (!bus->spbcap) {
		dev_err(bus->dev, "Address of SPB capability is NULL\n");
		return -EINVAL;
	}

	return readl(stream->fifo_addr);
}