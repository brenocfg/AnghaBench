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

/* Variables and functions */
 int /*<<< orphan*/  sharpsl_pcmcia_init_reset (struct soc_pcmcia_socket*) ; 

__attribute__((used)) static void sharpsl_pcmcia_socket_suspend(struct soc_pcmcia_socket *skt)
{
	sharpsl_pcmcia_init_reset(skt);
}