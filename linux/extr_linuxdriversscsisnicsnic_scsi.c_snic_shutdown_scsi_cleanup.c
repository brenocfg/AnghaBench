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
struct snic {int /*<<< orphan*/  shost; } ;

/* Variables and functions */
 int /*<<< orphan*/  SCSI_NO_TAG ; 
 int /*<<< orphan*/  SNIC_HOST_INFO (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  snic_scsi_cleanup (struct snic*,int /*<<< orphan*/ ) ; 

void
snic_shutdown_scsi_cleanup(struct snic *snic)
{
	SNIC_HOST_INFO(snic->shost, "Shutdown time SCSI Cleanup.\n");

	snic_scsi_cleanup(snic, SCSI_NO_TAG);
}