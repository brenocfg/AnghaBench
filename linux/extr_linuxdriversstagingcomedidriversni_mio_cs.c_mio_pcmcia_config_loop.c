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
struct pcmcia_device {TYPE_1__** resource; } ;
struct TYPE_2__ {int start; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  IO_DATA_PATH_WIDTH ; 
 int /*<<< orphan*/  IO_DATA_PATH_WIDTH_16 ; 
 int pcmcia_request_io (struct pcmcia_device*) ; 

__attribute__((used)) static int mio_pcmcia_config_loop(struct pcmcia_device *p_dev, void *priv_data)
{
	int base, ret;

	p_dev->resource[0]->flags &= ~IO_DATA_PATH_WIDTH;
	p_dev->resource[0]->flags |= IO_DATA_PATH_WIDTH_16;

	for (base = 0x000; base < 0x400; base += 0x20) {
		p_dev->resource[0]->start = base;
		ret = pcmcia_request_io(p_dev);
		if (!ret)
			return 0;
	}
	return -ENODEV;
}