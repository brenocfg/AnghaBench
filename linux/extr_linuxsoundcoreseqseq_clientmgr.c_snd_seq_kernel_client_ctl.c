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
struct snd_seq_client {int dummy; } ;
struct ioctl_handler {unsigned int cmd; int (* func ) (struct snd_seq_client*,void*) ;} ;

/* Variables and functions */
 int ENOTTY ; 
 int ENXIO ; 
 int /*<<< orphan*/  _IOC_NR (unsigned int) ; 
 int /*<<< orphan*/  _IOC_TYPE (unsigned int) ; 
 struct snd_seq_client* clientptr (int) ; 
 struct ioctl_handler* ioctl_handlers ; 
 int /*<<< orphan*/  pr_debug (char*,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub1 (struct snd_seq_client*,void*) ; 

int snd_seq_kernel_client_ctl(int clientid, unsigned int cmd, void *arg)
{
	const struct ioctl_handler *handler;
	struct snd_seq_client *client;

	client = clientptr(clientid);
	if (client == NULL)
		return -ENXIO;

	for (handler = ioctl_handlers; handler->cmd > 0; ++handler) {
		if (handler->cmd == cmd)
			return handler->func(client, arg);
	}

	pr_debug("ALSA: seq unknown ioctl() 0x%x (type='%c', number=0x%02x)\n",
		 cmd, _IOC_TYPE(cmd), _IOC_NR(cmd));
	return -ENOTTY;
}