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
struct soc_pcmcia_timing {int io; int attr; int mem; } ;
struct soc_pcmcia_socket {int /*<<< orphan*/  nr; int /*<<< orphan*/  clk; } ;

/* Variables and functions */
 unsigned long MECR ; 
 int /*<<< orphan*/  MECR_BSA_GET (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MECR_BSIO_GET (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MECR_BSM_GET (unsigned long,int /*<<< orphan*/ ) ; 
 int clk_get_rate (int /*<<< orphan*/ ) ; 
 int sa1100_pcmcia_cmd_time (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  soc_common_pcmcia_get_timing (struct soc_pcmcia_socket*,struct soc_pcmcia_timing*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int,int) ; 

__attribute__((used)) static int
sa1100_pcmcia_show_timing(struct soc_pcmcia_socket *skt, char *buf)
{
	struct soc_pcmcia_timing timing;
	unsigned int clock = clk_get_rate(skt->clk) / 1000;
	unsigned long mecr = MECR;
	char *p = buf;

	soc_common_pcmcia_get_timing(skt, &timing);

	p+=sprintf(p, "I/O      : %uns (%uns)\n", timing.io,
		   sa1100_pcmcia_cmd_time(clock, MECR_BSIO_GET(mecr, skt->nr)));

	p+=sprintf(p, "attribute: %uns (%uns)\n", timing.attr,
		   sa1100_pcmcia_cmd_time(clock, MECR_BSA_GET(mecr, skt->nr)));

	p+=sprintf(p, "common   : %uns (%uns)\n", timing.mem,
		   sa1100_pcmcia_cmd_time(clock, MECR_BSM_GET(mecr, skt->nr)));

	return p - buf;
}