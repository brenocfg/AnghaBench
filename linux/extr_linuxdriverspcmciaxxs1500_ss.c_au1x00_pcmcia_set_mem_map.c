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
struct xxs1500_pcmcia_sock {scalar_t__ phys_mem; scalar_t__ phys_attr; } ;
struct pcmcia_socket {int dummy; } ;
struct pccard_mem_map {int flags; scalar_t__ card_start; scalar_t__ static_start; } ;

/* Variables and functions */
 int MAP_ATTRIB ; 
 struct xxs1500_pcmcia_sock* to_xxs_socket (struct pcmcia_socket*) ; 

__attribute__((used)) static int au1x00_pcmcia_set_mem_map(struct pcmcia_socket *skt,
				     struct pccard_mem_map *map)
{
	struct xxs1500_pcmcia_sock *sock = to_xxs_socket(skt);

	if (map->flags & MAP_ATTRIB)
		map->static_start = sock->phys_attr + map->card_start;
	else
		map->static_start = sock->phys_mem + map->card_start;

	return 0;
}