#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint32_t ;
struct scsi_qla_host {int /*<<< orphan*/  host_no; } ;
struct scsi_cmnd {scalar_t__ sense_buffer; int result; TYPE_1__* device; } ;
struct rsp_que {TYPE_2__* status_srb; } ;
struct TYPE_8__ {struct scsi_qla_host* vha; } ;
typedef  TYPE_2__ srb_t ;
struct TYPE_7__ {int /*<<< orphan*/  lun; int /*<<< orphan*/  id; } ;

/* Variables and functions */
 struct scsi_cmnd* GET_CMD_SP (TYPE_2__*) ; 
 scalar_t__ SCSI_SENSE_BUFFERSIZE ; 
 int /*<<< orphan*/  SET_CMD_SENSE_LEN (TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  SET_CMD_SENSE_PTR (TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  ql_dbg (scalar_t__,struct scsi_qla_host*,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct scsi_cmnd*) ; 
 scalar_t__ ql_dbg_buffer ; 
 scalar_t__ ql_dbg_io ; 
 int /*<<< orphan*/  ql_dump_buffer (scalar_t__,struct scsi_qla_host*,int,scalar_t__,scalar_t__) ; 

__attribute__((used)) static inline void
qla2x00_handle_sense(srb_t *sp, uint8_t *sense_data, uint32_t par_sense_len,
		     uint32_t sense_len, struct rsp_que *rsp, int res)
{
	struct scsi_qla_host *vha = sp->vha;
	struct scsi_cmnd *cp = GET_CMD_SP(sp);
	uint32_t track_sense_len;

	if (sense_len >= SCSI_SENSE_BUFFERSIZE)
		sense_len = SCSI_SENSE_BUFFERSIZE;

	SET_CMD_SENSE_LEN(sp, sense_len);
	SET_CMD_SENSE_PTR(sp, cp->sense_buffer);
	track_sense_len = sense_len;

	if (sense_len > par_sense_len)
		sense_len = par_sense_len;

	memcpy(cp->sense_buffer, sense_data, sense_len);

	SET_CMD_SENSE_PTR(sp, cp->sense_buffer + sense_len);
	track_sense_len -= sense_len;
	SET_CMD_SENSE_LEN(sp, track_sense_len);

	if (track_sense_len != 0) {
		rsp->status_srb = sp;
		cp->result = res;
	}

	if (sense_len) {
		ql_dbg(ql_dbg_io + ql_dbg_buffer, vha, 0x301c,
		    "Check condition Sense data, nexus%ld:%d:%llu cmd=%p.\n",
		    sp->vha->host_no, cp->device->id, cp->device->lun,
		    cp);
		ql_dump_buffer(ql_dbg_io + ql_dbg_buffer, vha, 0x302b,
		    cp->sense_buffer, sense_len);
	}
}