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
struct pcmcia_device {TYPE_1__* socket; } ;
struct TYPE_2__ {int /*<<< orphan*/  present; } ;

/* Variables and functions */
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 struct pcmcia_device* pcmcia_get_dev (struct pcmcia_device*) ; 
 int /*<<< orphan*/  pcmcia_put_dev (struct pcmcia_device*) ; 

struct pcmcia_device *pcmcia_dev_present(struct pcmcia_device *_p_dev)
{
	struct pcmcia_device *p_dev;
	struct pcmcia_device *ret = NULL;

	p_dev = pcmcia_get_dev(_p_dev);
	if (!p_dev)
		return NULL;

	if (atomic_read(&p_dev->socket->present) != 0)
		ret = p_dev;

	pcmcia_put_dev(p_dev);
	return ret;
}