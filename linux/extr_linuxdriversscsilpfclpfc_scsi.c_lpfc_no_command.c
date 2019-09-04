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
struct scsi_cmnd {int dummy; } ;
struct Scsi_Host {int dummy; } ;

/* Variables and functions */
 int SCSI_MLQUEUE_HOST_BUSY ; 

__attribute__((used)) static int
lpfc_no_command(struct Scsi_Host *shost, struct scsi_cmnd *cmnd)
{
	return SCSI_MLQUEUE_HOST_BUSY;
}