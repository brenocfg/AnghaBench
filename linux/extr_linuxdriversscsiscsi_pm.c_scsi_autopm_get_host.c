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
struct Scsi_Host {int /*<<< orphan*/  shost_gendev; } ;

/* Variables and functions */
 int EACCES ; 
 int pm_runtime_get_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_put_sync (int /*<<< orphan*/ *) ; 

int scsi_autopm_get_host(struct Scsi_Host *shost)
{
	int	err;

	err = pm_runtime_get_sync(&shost->shost_gendev);
	if (err < 0 && err !=-EACCES)
		pm_runtime_put_sync(&shost->shost_gendev);
	else
		err = 0;
	return err;
}