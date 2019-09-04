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
struct pcmcia_socket {int /*<<< orphan*/  sock; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  bus_for_each_dev (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct pcmcia_socket*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcmcia_bus_resume_callback ; 
 int /*<<< orphan*/  pcmcia_bus_type ; 

__attribute__((used)) static int pcmcia_bus_resume(struct pcmcia_socket *skt)
{
	dev_dbg(&skt->dev, "resuming socket %d\n", skt->sock);
	bus_for_each_dev(&pcmcia_bus_type, NULL, skt, pcmcia_bus_resume_callback);
	return 0;
}