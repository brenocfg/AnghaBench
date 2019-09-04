#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct resource {int flags; } ;
struct pcmcia_socket {int /*<<< orphan*/  ops_mutex; TYPE_2__* win; TYPE_1__* ops; } ;
struct pcmcia_device {int /*<<< orphan*/  dev; struct pcmcia_socket* socket; } ;
struct TYPE_4__ {unsigned int card_start; } ;
struct TYPE_3__ {int (* set_mem_map ) (struct pcmcia_socket*,TYPE_2__*) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int IORESOURCE_BITS ; 
 unsigned int MAX_WIN ; 
 int WIN_FLAGS_REQ ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int stub1 (struct pcmcia_socket*,TYPE_2__*) ; 

int pcmcia_map_mem_page(struct pcmcia_device *p_dev, struct resource *res,
			unsigned int offset)
{
	struct pcmcia_socket *s = p_dev->socket;
	unsigned int w;
	int ret;

	w = ((res->flags & IORESOURCE_BITS & WIN_FLAGS_REQ) >> 2) - 1;
	if (w >= MAX_WIN)
		return -EINVAL;

	mutex_lock(&s->ops_mutex);
	s->win[w].card_start = offset;
	ret = s->ops->set_mem_map(s, &s->win[w]);
	if (ret)
		dev_warn(&p_dev->dev, "failed to set_mem_map\n");
	mutex_unlock(&s->ops_mutex);
	return ret;
}