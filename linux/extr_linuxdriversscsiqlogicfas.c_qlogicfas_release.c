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
struct qlogicfas408_priv {int dummy; } ;
struct Scsi_Host {scalar_t__ n_io_port; scalar_t__ io_port; scalar_t__ irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_irq (scalar_t__,struct Scsi_Host*) ; 
 struct qlogicfas408_priv* get_priv_by_host (struct Scsi_Host*) ; 
 int /*<<< orphan*/  qlogicfas408_disable_ints (struct qlogicfas408_priv*) ; 
 int /*<<< orphan*/  release_region (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  scsi_host_put (struct Scsi_Host*) ; 
 int /*<<< orphan*/  scsi_remove_host (struct Scsi_Host*) ; 

__attribute__((used)) static int qlogicfas_release(struct Scsi_Host *shost)
{
	struct qlogicfas408_priv *priv = get_priv_by_host(shost);

	scsi_remove_host(shost);
	if (shost->irq) {
		qlogicfas408_disable_ints(priv);	
		free_irq(shost->irq, shost);
	}
	if (shost->io_port && shost->n_io_port)
		release_region(shost->io_port, shost->n_io_port);
	scsi_host_put(shost);

	return 0;
}