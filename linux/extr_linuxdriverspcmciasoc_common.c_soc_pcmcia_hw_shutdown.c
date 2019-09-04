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
struct soc_pcmcia_socket {int /*<<< orphan*/  stat; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __soc_pcmcia_hw_shutdown (struct soc_pcmcia_socket*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void soc_pcmcia_hw_shutdown(struct soc_pcmcia_socket *skt)
{
	__soc_pcmcia_hw_shutdown(skt, ARRAY_SIZE(skt->stat));
}