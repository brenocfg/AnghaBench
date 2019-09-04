#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct zfcp_fsf_req {int dummy; } ;
struct zfcp_adapter {TYPE_2__* dbf; } ;
struct scsi_cmnd {TYPE_3__* device; } ;
struct TYPE_6__ {TYPE_1__* host; } ;
struct TYPE_5__ {int /*<<< orphan*/  scsi; } ;
struct TYPE_4__ {scalar_t__* hostdata; } ;

/* Variables and functions */
 scalar_t__ debug_level_enabled (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  zfcp_dbf_scsi_common (char*,int,TYPE_3__*,struct scsi_cmnd*,struct zfcp_fsf_req*) ; 

__attribute__((used)) static inline
void _zfcp_dbf_scsi(char *tag, int level, struct scsi_cmnd *scmd,
		   struct zfcp_fsf_req *req)
{
	struct zfcp_adapter *adapter = (struct zfcp_adapter *)
					scmd->device->host->hostdata[0];

	if (debug_level_enabled(adapter->dbf->scsi, level))
		zfcp_dbf_scsi_common(tag, level, scmd->device, scmd, req);
}