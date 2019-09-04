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
struct scsi_host_template {int (* eh_abort_handler ) (struct scsi_cmnd*) ;} ;
struct scsi_cmnd {int dummy; } ;

/* Variables and functions */
 int FAILED ; 
 int stub1 (struct scsi_cmnd*) ; 

__attribute__((used)) static int scsi_try_to_abort_cmd(struct scsi_host_template *hostt,
				 struct scsi_cmnd *scmd)
{
	if (!hostt->eh_abort_handler)
		return FAILED;

	return hostt->eh_abort_handler(scmd);
}