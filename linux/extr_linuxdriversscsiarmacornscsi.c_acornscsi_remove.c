#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct expansion_card {int dummy; } ;
struct Scsi_Host {int /*<<< orphan*/  irq; scalar_t__ hostdata; } ;
struct TYPE_6__ {int /*<<< orphan*/  issue; int /*<<< orphan*/  disconnected; } ;
struct TYPE_5__ {int /*<<< orphan*/  msgs; } ;
struct TYPE_7__ {scalar_t__ base; scalar_t__ fast; TYPE_2__ queues; TYPE_1__ scsi; } ;
typedef  TYPE_3__ AS_Host ;

/* Variables and functions */
 scalar_t__ PAGE_REG ; 
 struct Scsi_Host* ecard_get_drvdata (struct expansion_card*) ; 
 int /*<<< orphan*/  ecard_release_resources (struct expansion_card*) ; 
 int /*<<< orphan*/  ecard_set_drvdata (struct expansion_card*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ecardm_iounmap (struct expansion_card*,scalar_t__) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  msgqueue_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  queue_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scsi_host_put (struct Scsi_Host*) ; 
 int /*<<< orphan*/  scsi_remove_host (struct Scsi_Host*) ; 
 int /*<<< orphan*/  writeb (int,scalar_t__) ; 

__attribute__((used)) static void acornscsi_remove(struct expansion_card *ec)
{
	struct Scsi_Host *host = ecard_get_drvdata(ec);
	AS_Host *ashost = (AS_Host *)host->hostdata;

	ecard_set_drvdata(ec, NULL);
	scsi_remove_host(host);

	/*
	 * Put card into RESET state
	 */
	writeb(0x80, ashost->fast + PAGE_REG);

	free_irq(host->irq, ashost);

	msgqueue_free(&ashost->scsi.msgs);
	queue_free(&ashost->queues.disconnected);
	queue_free(&ashost->queues.issue);
	ecardm_iounmap(ec, ashost->fast);
	ecardm_iounmap(ec, ashost->base);
	scsi_host_put(host);
	ecard_release_resources(ec);
}