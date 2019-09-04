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
typedef  void* u32 ;
struct zfcp_dbf_scsi {int scsi_result; unsigned int scsi_id; struct zfcp_dbf_scsi* scsi_opcode; int /*<<< orphan*/  host_scribble; void* scsi_lun_64_hi; void* scsi_lun; int /*<<< orphan*/  fcp_rsp_info; int /*<<< orphan*/  scsi_allowed; int /*<<< orphan*/  scsi_retries; int /*<<< orphan*/  id; int /*<<< orphan*/  tag; } ;
struct zfcp_dbf {int /*<<< orphan*/  scsi_lock; int /*<<< orphan*/  scsi; struct zfcp_dbf_scsi scsi_buf; } ;
struct zfcp_adapter {struct zfcp_dbf* dbf; } ;

/* Variables and functions */
 int ZFCP_DBF_INVALID_LUN ; 
 int /*<<< orphan*/  ZFCP_DBF_SCSI_CMND ; 
 int ZFCP_DBF_SCSI_OPCODE ; 
 int /*<<< orphan*/  ZFCP_DBF_TAG_LEN ; 
 int /*<<< orphan*/  debug_event (int /*<<< orphan*/ ,int const,struct zfcp_dbf_scsi*,int) ; 
 int /*<<< orphan*/  debug_level_enabled (int /*<<< orphan*/ ,int const) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct zfcp_dbf_scsi*,int,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ unlikely (int) ; 

void zfcp_dbf_scsi_eh(char *tag, struct zfcp_adapter *adapter,
		      unsigned int scsi_id, int ret)
{
	struct zfcp_dbf *dbf = adapter->dbf;
	struct zfcp_dbf_scsi *rec = &dbf->scsi_buf;
	unsigned long flags;
	static int const level = 1;

	if (unlikely(!debug_level_enabled(adapter->dbf->scsi, level)))
		return;

	spin_lock_irqsave(&dbf->scsi_lock, flags);
	memset(rec, 0, sizeof(*rec));

	memcpy(rec->tag, tag, ZFCP_DBF_TAG_LEN);
	rec->id = ZFCP_DBF_SCSI_CMND;
	rec->scsi_result = ret; /* re-use field, int is 4 bytes and fits */
	rec->scsi_retries = ~0;
	rec->scsi_allowed = ~0;
	rec->fcp_rsp_info = ~0;
	rec->scsi_id = scsi_id;
	rec->scsi_lun = (u32)ZFCP_DBF_INVALID_LUN;
	rec->scsi_lun_64_hi = (u32)(ZFCP_DBF_INVALID_LUN >> 32);
	rec->host_scribble = ~0;
	memset(rec->scsi_opcode, 0xff, ZFCP_DBF_SCSI_OPCODE);

	debug_event(dbf->scsi, level, rec, sizeof(*rec));
	spin_unlock_irqrestore(&dbf->scsi_lock, flags);
}