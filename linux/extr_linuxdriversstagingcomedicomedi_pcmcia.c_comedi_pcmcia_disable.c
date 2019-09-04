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
struct pcmcia_device {int dummy; } ;
struct comedi_device {int dummy; } ;

/* Variables and functions */
 struct pcmcia_device* comedi_to_pcmcia_dev (struct comedi_device*) ; 
 int /*<<< orphan*/  pcmcia_disable_device (struct pcmcia_device*) ; 

void comedi_pcmcia_disable(struct comedi_device *dev)
{
	struct pcmcia_device *link = comedi_to_pcmcia_dev(dev);

	if (link)
		pcmcia_disable_device(link);
}