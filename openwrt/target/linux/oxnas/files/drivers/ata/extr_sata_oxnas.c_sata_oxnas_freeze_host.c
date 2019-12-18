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
struct sata_oxnas_host_priv {int /*<<< orphan*/  port_in_eh; } ;
struct ata_port {int /*<<< orphan*/  port_no; TYPE_1__* host; } ;
struct TYPE_2__ {struct sata_oxnas_host_priv* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DPRINTK (char*) ; 
 int /*<<< orphan*/  smp_wmb () ; 

void sata_oxnas_freeze_host(struct ata_port *ap)
{
	struct sata_oxnas_host_priv *hd = ap->host->private_data;

	DPRINTK("ENTER\n");
	hd->port_in_eh |= BIT(ap->port_no);
	smp_wmb();
}