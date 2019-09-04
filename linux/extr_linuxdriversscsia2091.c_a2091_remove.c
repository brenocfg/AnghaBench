#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  start; } ;
struct zorro_dev {TYPE_2__ resource; } ;
struct a2091_hostdata {TYPE_1__* regs; } ;
struct Scsi_Host {int dummy; } ;
struct TYPE_3__ {scalar_t__ CNTR; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_AMIGA_PORTS ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct Scsi_Host*) ; 
 int /*<<< orphan*/  release_mem_region (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  scsi_host_put (struct Scsi_Host*) ; 
 int /*<<< orphan*/  scsi_remove_host (struct Scsi_Host*) ; 
 struct a2091_hostdata* shost_priv (struct Scsi_Host*) ; 
 struct Scsi_Host* zorro_get_drvdata (struct zorro_dev*) ; 

__attribute__((used)) static void a2091_remove(struct zorro_dev *z)
{
	struct Scsi_Host *instance = zorro_get_drvdata(z);
	struct a2091_hostdata *hdata = shost_priv(instance);

	hdata->regs->CNTR = 0;
	scsi_remove_host(instance);
	free_irq(IRQ_AMIGA_PORTS, instance);
	scsi_host_put(instance);
	release_mem_region(z->resource.start, 256);
}