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
typedef  int /*<<< orphan*/  u8 ;
struct seq_file {int dummy; } ;
struct scsi_device {scalar_t__ lun; TYPE_1__* sdev_target; } ;
struct ahc_linux_device {int /*<<< orphan*/  qfrozen; int /*<<< orphan*/  maxtags; int /*<<< orphan*/  openings; int /*<<< orphan*/  active; int /*<<< orphan*/  commands_issued; } ;
struct TYPE_2__ {int /*<<< orphan*/  id; scalar_t__ channel; } ;

/* Variables and functions */
 struct ahc_linux_device* scsi_transport_device_data (struct scsi_device*) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static void
ahc_dump_device_state(struct seq_file *m, struct scsi_device *sdev)
{
	struct ahc_linux_device *dev = scsi_transport_device_data(sdev);

	seq_printf(m, "\tChannel %c Target %d Lun %d Settings\n",
		  sdev->sdev_target->channel + 'A',
		   sdev->sdev_target->id, (u8)sdev->lun);

	seq_printf(m, "\t\tCommands Queued %ld\n", dev->commands_issued);
	seq_printf(m, "\t\tCommands Active %d\n", dev->active);
	seq_printf(m, "\t\tCommand Openings %d\n", dev->openings);
	seq_printf(m, "\t\tMax Tagged Openings %d\n", dev->maxtags);
	seq_printf(m, "\t\tDevice Queue Frozen Count %d\n", dev->qfrozen);
}