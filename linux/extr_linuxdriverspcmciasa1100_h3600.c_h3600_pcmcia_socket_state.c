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
struct soc_pcmcia_socket {int dummy; } ;
struct pcmcia_state {scalar_t__ vs_Xv; scalar_t__ vs_3v; scalar_t__ bvd2; scalar_t__ bvd1; } ;

/* Variables and functions */

__attribute__((used)) static void
h3600_pcmcia_socket_state(struct soc_pcmcia_socket *skt, struct pcmcia_state *state)
{
	state->bvd1 = 0;
	state->bvd2 = 0;
	state->vs_3v = 0;
	state->vs_Xv = 0;
}