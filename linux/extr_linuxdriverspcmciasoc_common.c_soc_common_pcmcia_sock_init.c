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
struct soc_pcmcia_socket {TYPE_1__* ops; } ;
struct pcmcia_socket {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* socket_init ) (struct soc_pcmcia_socket*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  debug (struct soc_pcmcia_socket*,int,char*) ; 
 int /*<<< orphan*/  soc_pcmcia_hw_enable (struct soc_pcmcia_socket*) ; 
 int /*<<< orphan*/  stub1 (struct soc_pcmcia_socket*) ; 
 struct soc_pcmcia_socket* to_soc_pcmcia_socket (struct pcmcia_socket*) ; 

__attribute__((used)) static int soc_common_pcmcia_sock_init(struct pcmcia_socket *sock)
{
	struct soc_pcmcia_socket *skt = to_soc_pcmcia_socket(sock);

	debug(skt, 2, "initializing socket\n");
	if (skt->ops->socket_init)
		skt->ops->socket_init(skt);
	soc_pcmcia_hw_enable(skt);
	return 0;
}