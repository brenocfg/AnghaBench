#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct soc_pcmcia_socket {int /*<<< orphan*/  vcc; } ;
struct TYPE_3__ {int /*<<< orphan*/  Vcc; } ;
typedef  TYPE_1__ socket_state_t ;

/* Variables and functions */
 int soc_pcmcia_regulator_set (struct soc_pcmcia_socket*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sa11x0_cf_configure_socket(struct soc_pcmcia_socket *skt,
	const socket_state_t *state)
{
	return soc_pcmcia_regulator_set(skt, &skt->vcc, state->Vcc);
}