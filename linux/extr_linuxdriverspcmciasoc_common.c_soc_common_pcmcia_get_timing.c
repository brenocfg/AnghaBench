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
struct soc_pcmcia_timing {void* attr; void* mem; void* io; } ;
struct soc_pcmcia_socket {int /*<<< orphan*/  spd_attr; int /*<<< orphan*/  spd_mem; int /*<<< orphan*/  spd_io; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAX_IO_WIN ; 
 int /*<<< orphan*/  MAX_WIN ; 
 int /*<<< orphan*/  SOC_PCMCIA_3V_MEM_ACCESS ; 
 int /*<<< orphan*/  SOC_PCMCIA_IO_ACCESS ; 
 void* calc_speed (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void soc_common_pcmcia_get_timing(struct soc_pcmcia_socket *skt,
	struct soc_pcmcia_timing *timing)
{
	timing->io =
		calc_speed(skt->spd_io, MAX_IO_WIN, SOC_PCMCIA_IO_ACCESS);
	timing->mem =
		calc_speed(skt->spd_mem, MAX_WIN, SOC_PCMCIA_3V_MEM_ACCESS);
	timing->attr =
		calc_speed(skt->spd_attr, MAX_WIN, SOC_PCMCIA_3V_MEM_ACCESS);
}