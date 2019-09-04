#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
struct zfcp_fsf_req {int dummy; } ;
struct zfcp_adapter {TYPE_2__* dbf; } ;
struct scsi_device {TYPE_1__* host; } ;
struct TYPE_4__ {int /*<<< orphan*/  scsi; } ;
struct TYPE_3__ {scalar_t__* hostdata; } ;

/* Variables and functions */
 scalar_t__ FCP_TMF_TGT_RESET ; 
 int ZFCP_DBF_TAG_LEN ; 
 int /*<<< orphan*/  debug_level_enabled (int /*<<< orphan*/ ,int const) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  zfcp_dbf_scsi_common (char*,int const,struct scsi_device*,int /*<<< orphan*/ *,struct zfcp_fsf_req*) ; 

__attribute__((used)) static inline
void zfcp_dbf_scsi_devreset(char *tag, struct scsi_device *sdev, u8 flag,
			    struct zfcp_fsf_req *fsf_req)
{
	struct zfcp_adapter *adapter = (struct zfcp_adapter *)
					sdev->host->hostdata[0];
	char tmp_tag[ZFCP_DBF_TAG_LEN];
	static int const level = 1;

	if (unlikely(!debug_level_enabled(adapter->dbf->scsi, level)))
		return;

	if (flag == FCP_TMF_TGT_RESET)
		memcpy(tmp_tag, "tr_", 3);
	else
		memcpy(tmp_tag, "lr_", 3);

	memcpy(&tmp_tag[3], tag, 4);
	zfcp_dbf_scsi_common(tmp_tag, level, sdev, NULL, fsf_req);
}