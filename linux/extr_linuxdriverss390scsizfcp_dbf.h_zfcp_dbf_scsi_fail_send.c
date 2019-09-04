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

/* Variables and functions */
 int /*<<< orphan*/  _zfcp_dbf_scsi (char*,int,struct scsi_cmnd*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline
void zfcp_dbf_scsi_fail_send(struct scsi_cmnd *scmd)
{
	_zfcp_dbf_scsi("rsl_fai", 4, scmd, NULL);
}