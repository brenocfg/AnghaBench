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
struct ipr_ioasa_gata {int /*<<< orphan*/  hob_lbah; int /*<<< orphan*/  hob_lbam; int /*<<< orphan*/  hob_lbal; int /*<<< orphan*/  hob_nsect; int /*<<< orphan*/  status; int /*<<< orphan*/  device; int /*<<< orphan*/  lbah; int /*<<< orphan*/  lbam; int /*<<< orphan*/  lbal; int /*<<< orphan*/  nsect; int /*<<< orphan*/  error; } ;
struct ipr_sata_port {struct ipr_ioasa_gata ioasa; } ;
struct ata_taskfile {int /*<<< orphan*/  hob_lbah; int /*<<< orphan*/  hob_lbam; int /*<<< orphan*/  hob_lbal; int /*<<< orphan*/  hob_nsect; int /*<<< orphan*/  command; int /*<<< orphan*/  device; int /*<<< orphan*/  lbah; int /*<<< orphan*/  lbam; int /*<<< orphan*/  lbal; int /*<<< orphan*/  nsect; int /*<<< orphan*/  feature; } ;
struct ata_queued_cmd {struct ata_taskfile result_tf; TYPE_1__* ap; } ;
struct TYPE_2__ {struct ipr_sata_port* private_data; } ;

/* Variables and functions */

__attribute__((used)) static bool ipr_qc_fill_rtf(struct ata_queued_cmd *qc)
{
	struct ipr_sata_port *sata_port = qc->ap->private_data;
	struct ipr_ioasa_gata *g = &sata_port->ioasa;
	struct ata_taskfile *tf = &qc->result_tf;

	tf->feature = g->error;
	tf->nsect = g->nsect;
	tf->lbal = g->lbal;
	tf->lbam = g->lbam;
	tf->lbah = g->lbah;
	tf->device = g->device;
	tf->command = g->status;
	tf->hob_nsect = g->hob_nsect;
	tf->hob_lbal = g->hob_lbal;
	tf->hob_lbam = g->hob_lbam;
	tf->hob_lbah = g->hob_lbah;

	return true;
}