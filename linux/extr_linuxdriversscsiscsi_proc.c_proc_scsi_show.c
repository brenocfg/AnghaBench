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
struct seq_file {struct Scsi_Host* private; } ;
struct Scsi_Host {TYPE_1__* hostt; } ;
struct TYPE_2__ {int (* show_info ) (struct seq_file*,struct Scsi_Host*) ;} ;

/* Variables and functions */
 int stub1 (struct seq_file*,struct Scsi_Host*) ; 

__attribute__((used)) static int proc_scsi_show(struct seq_file *m, void *v)
{
	struct Scsi_Host *shost = m->private;
	return shost->hostt->show_info(m, shost);
}