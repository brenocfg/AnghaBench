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
struct sa1111_pcmcia_socket {int /*<<< orphan*/  soc; struct sa1111_pcmcia_socket* next; } ;
struct TYPE_2__ {int /*<<< orphan*/  start; } ;
struct sa1111_dev {TYPE_1__ res; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 struct sa1111_pcmcia_socket* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_set_drvdata (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct sa1111_pcmcia_socket*) ; 
 int /*<<< orphan*/  release_mem_region (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sa1111_disable_device (struct sa1111_dev*) ; 
 int /*<<< orphan*/  soc_pcmcia_remove_one (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pcmcia_remove(struct sa1111_dev *dev)
{
	struct sa1111_pcmcia_socket *next, *s = dev_get_drvdata(&dev->dev);

	dev_set_drvdata(&dev->dev, NULL);

	for (; s; s = next) {
		next = s->next;
		soc_pcmcia_remove_one(&s->soc);
		kfree(s);
	}

	release_mem_region(dev->res.start, 512);
	sa1111_disable_device(dev);
	return 0;
}