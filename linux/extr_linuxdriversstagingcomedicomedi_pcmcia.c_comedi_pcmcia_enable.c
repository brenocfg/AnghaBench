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
 int ENODEV ; 
 int comedi_pcmcia_conf_check (struct pcmcia_device*,void*) ; 
 struct pcmcia_device* comedi_to_pcmcia_dev (struct comedi_device*) ; 
 int pcmcia_enable_device (struct pcmcia_device*) ; 
 int pcmcia_loop_config (struct pcmcia_device*,int (*) (struct pcmcia_device*,void*),int /*<<< orphan*/ *) ; 

int comedi_pcmcia_enable(struct comedi_device *dev,
			 int (*conf_check)(struct pcmcia_device *p_dev,
					   void *priv_data))
{
	struct pcmcia_device *link = comedi_to_pcmcia_dev(dev);
	int ret;

	if (!link)
		return -ENODEV;

	if (!conf_check)
		conf_check = comedi_pcmcia_conf_check;

	ret = pcmcia_loop_config(link, conf_check, NULL);
	if (ret)
		return ret;

	return pcmcia_enable_device(link);
}