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
struct sysfs_bin_attrs {int /*<<< orphan*/  attr; scalar_t__ name; } ;
struct TYPE_2__ {int /*<<< orphan*/  kobj; } ;
struct Scsi_Host {TYPE_1__ shost_gendev; } ;

/* Variables and functions */
 int /*<<< orphan*/  sysfs_remove_bin_file (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
qedf_remove_sysfs_attr(struct Scsi_Host *shost, struct sysfs_bin_attrs *iter)
{
	for (; iter->name; iter++)
		sysfs_remove_bin_file(&shost->shost_gendev.kobj, iter->attr);
}