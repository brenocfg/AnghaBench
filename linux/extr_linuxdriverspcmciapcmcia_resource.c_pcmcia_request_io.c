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
struct resource {scalar_t__ start; int /*<<< orphan*/  flags; scalar_t__ end; } ;
struct pcmcia_socket {int state; int /*<<< orphan*/  ops_mutex; } ;
struct pcmcia_device {int _io; int /*<<< orphan*/  dev; int /*<<< orphan*/  io_lines; TYPE_1__* function_config; struct pcmcia_socket* socket; } ;
struct TYPE_2__ {int state; struct resource* io; } ;
typedef  TYPE_1__ config_t ;

/* Variables and functions */
 int CONFIG_IO_REQ ; 
 int CONFIG_LOCKED ; 
 int EINVAL ; 
 int SOCKET_PRESENT ; 
 int alloc_io_space (struct pcmcia_socket*,struct resource*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  release_io_space (struct pcmcia_socket*,struct resource*) ; 
 scalar_t__ resource_size (struct resource*) ; 

int pcmcia_request_io(struct pcmcia_device *p_dev)
{
	struct pcmcia_socket *s = p_dev->socket;
	config_t *c = p_dev->function_config;
	int ret = -EINVAL;

	mutex_lock(&s->ops_mutex);
	dev_dbg(&p_dev->dev, "pcmcia_request_io: %pR , %pR",
		&c->io[0], &c->io[1]);

	if (!(s->state & SOCKET_PRESENT)) {
		dev_dbg(&p_dev->dev, "pcmcia_request_io: No card present\n");
		goto out;
	}

	if (c->state & CONFIG_LOCKED) {
		dev_dbg(&p_dev->dev, "Configuration is locked\n");
		goto out;
	}
	if (c->state & CONFIG_IO_REQ) {
		dev_dbg(&p_dev->dev, "IO already configured\n");
		goto out;
	}

	ret = alloc_io_space(s, &c->io[0], p_dev->io_lines);
	if (ret)
		goto out;

	if (c->io[1].end) {
		ret = alloc_io_space(s, &c->io[1], p_dev->io_lines);
		if (ret) {
			struct resource tmp = c->io[0];
			/* release the previously allocated resource */
			release_io_space(s, &c->io[0]);
			/* but preserve the settings, for they worked... */
			c->io[0].end = resource_size(&tmp);
			c->io[0].start = tmp.start;
			c->io[0].flags = tmp.flags;
			goto out;
		}
	} else
		c->io[1].start = 0;

	c->state |= CONFIG_IO_REQ;
	p_dev->_io = 1;

	dev_dbg(&p_dev->dev, "pcmcia_request_io succeeded: %pR , %pR",
		&c->io[0], &c->io[1]);
out:
	mutex_unlock(&s->ops_mutex);

	return ret;
}