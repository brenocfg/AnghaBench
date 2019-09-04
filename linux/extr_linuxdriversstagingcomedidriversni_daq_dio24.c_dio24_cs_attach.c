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

/* Variables and functions */
 int comedi_pcmcia_auto_config (struct pcmcia_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  driver_dio24 ; 

__attribute__((used)) static int dio24_cs_attach(struct pcmcia_device *link)
{
	return comedi_pcmcia_auto_config(link, &driver_dio24);
}