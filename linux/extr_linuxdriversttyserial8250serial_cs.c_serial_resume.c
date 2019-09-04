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
struct serial_info {int ndev; TYPE_1__* quirk; int /*<<< orphan*/ * line; } ;
struct pcmcia_device {struct serial_info* priv; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* wakeup ) (struct pcmcia_device*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  serial8250_resume_port (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct pcmcia_device*) ; 

__attribute__((used)) static int serial_resume(struct pcmcia_device *link)
{
	struct serial_info *info = link->priv;
	int i;

	for (i = 0; i < info->ndev; i++)
		serial8250_resume_port(info->line[i]);

	if (info->quirk && info->quirk->wakeup)
		info->quirk->wakeup(link);

	return 0;
}