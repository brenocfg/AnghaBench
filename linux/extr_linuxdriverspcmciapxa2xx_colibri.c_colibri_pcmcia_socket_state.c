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
struct soc_pcmcia_socket {int dummy; } ;
struct pcmcia_state {int detect; int ready; int bvd1; int bvd2; int vs_3v; scalar_t__ vs_Xv; } ;
struct TYPE_2__ {int /*<<< orphan*/  gpio; } ;

/* Variables and functions */
 size_t BVD1 ; 
 size_t BVD2 ; 
 size_t DETECT ; 
 size_t READY ; 
 TYPE_1__* colibri_pcmcia_gpios ; 
 int /*<<< orphan*/  gpio_get_value (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void colibri_pcmcia_socket_state(struct soc_pcmcia_socket *skt,
					struct pcmcia_state *state)
{

	state->detect = !!gpio_get_value(colibri_pcmcia_gpios[DETECT].gpio);
	state->ready  = !!gpio_get_value(colibri_pcmcia_gpios[READY].gpio);
	state->bvd1   = !!gpio_get_value(colibri_pcmcia_gpios[BVD1].gpio);
	state->bvd2   = !!gpio_get_value(colibri_pcmcia_gpios[BVD2].gpio);
	state->vs_3v  = 1;
	state->vs_Xv  = 0;
}