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
struct TYPE_2__ {int /*<<< orphan*/  port; int /*<<< orphan*/  client; } ;
struct snd_seq_port_info {TYPE_1__ addr; } ;
struct snd_seq_client_port {TYPE_1__ addr; } ;
struct snd_seq_client {int dummy; } ;

/* Variables and functions */
 int ENOENT ; 
 int ENXIO ; 
 int /*<<< orphan*/  snd_seq_client_unlock (struct snd_seq_client*) ; 
 struct snd_seq_client* snd_seq_client_use_ptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_seq_get_port_info (struct snd_seq_client_port*,struct snd_seq_port_info*) ; 
 struct snd_seq_client_port* snd_seq_port_query_nearest (struct snd_seq_client*,struct snd_seq_port_info*) ; 
 int /*<<< orphan*/  snd_seq_port_unlock (struct snd_seq_client_port*) ; 

__attribute__((used)) static int snd_seq_ioctl_query_next_port(struct snd_seq_client *client,
					 void *arg)
{
	struct snd_seq_port_info *info = arg;
	struct snd_seq_client *cptr;
	struct snd_seq_client_port *port = NULL;

	cptr = snd_seq_client_use_ptr(info->addr.client);
	if (cptr == NULL)
		return -ENXIO;

	/* search for next port */
	info->addr.port++;
	port = snd_seq_port_query_nearest(cptr, info);
	if (port == NULL) {
		snd_seq_client_unlock(cptr);
		return -ENOENT;
	}

	/* get port info */
	info->addr = port->addr;
	snd_seq_get_port_info(port, info);
	snd_seq_port_unlock(port);
	snd_seq_client_unlock(cptr);

	return 0;
}