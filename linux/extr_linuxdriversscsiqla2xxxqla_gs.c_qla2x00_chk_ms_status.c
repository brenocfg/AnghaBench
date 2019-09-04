#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint16_t ;
struct qla_hw_data {int dummy; } ;
struct TYPE_11__ {int /*<<< orphan*/  response; } ;
struct ct_sns_rsp {TYPE_1__ header; } ;
struct ct_rsp_hdr {int dummy; } ;
struct ct_entry_24xx {int /*<<< orphan*/  comp_status; } ;
struct TYPE_13__ {int /*<<< orphan*/  al_pa; int /*<<< orphan*/  area; int /*<<< orphan*/  domain; } ;
struct TYPE_14__ {TYPE_3__ b; } ;
struct TYPE_15__ {TYPE_4__ d_id; int /*<<< orphan*/  dpc_flags; struct qla_hw_data* hw; } ;
typedef  TYPE_5__ scsi_qla_host_t ;
struct TYPE_12__ {int /*<<< orphan*/  extended; } ;
struct TYPE_16__ {scalar_t__ entry_status; TYPE_2__ loop_id; int /*<<< orphan*/  status; } ;
typedef  TYPE_6__ ms_iocb_entry_t ;

/* Variables and functions */
#define  CS_COMPLETE 132 
#define  CS_DATA_OVERRUN 131 
#define  CS_DATA_UNDERRUN 130 
#define  CS_PORT_LOGGED_OUT 129 
#define  CS_TIMEOUT 128 
 int /*<<< orphan*/  CT_ACCEPT_RESPONSE ; 
 scalar_t__ IS_FWI2_CAPABLE (struct qla_hw_data*) ; 
 int /*<<< orphan*/  LOCAL_LOOP_UPDATE ; 
 int /*<<< orphan*/  LOOP_RESYNC_NEEDED ; 
 int NPH_SNS ; 
 int QLA_FUNCTION_FAILED ; 
 int QLA_FUNCTION_TIMEOUT ; 
 int QLA_INVALID_COMMAND ; 
 int QLA_NOT_LOGGED_IN ; 
 int QLA_SUCCESS ; 
 int SIMPLE_NAME_SERVER ; 
 int /*<<< orphan*/  cpu_to_be16 (int /*<<< orphan*/ ) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ql_dbg (scalar_t__,TYPE_5__*,int,char*,char const*,...) ; 
 int /*<<< orphan*/  ql_dbg_async ; 
 scalar_t__ ql_dbg_buffer ; 
 scalar_t__ ql_dbg_disc ; 
 int /*<<< orphan*/  ql_dump_buffer (scalar_t__,TYPE_5__*,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int
qla2x00_chk_ms_status(scsi_qla_host_t *vha, ms_iocb_entry_t *ms_pkt,
    struct ct_sns_rsp *ct_rsp, const char *routine)
{
	int rval;
	uint16_t comp_status;
	struct qla_hw_data *ha = vha->hw;
	bool lid_is_sns = false;

	rval = QLA_FUNCTION_FAILED;
	if (ms_pkt->entry_status != 0) {
		ql_dbg(ql_dbg_disc, vha, 0x2031,
		    "%s failed, error status (%x) on port_id: %02x%02x%02x.\n",
		    routine, ms_pkt->entry_status, vha->d_id.b.domain,
		    vha->d_id.b.area, vha->d_id.b.al_pa);
	} else {
		if (IS_FWI2_CAPABLE(ha))
			comp_status = le16_to_cpu(
			    ((struct ct_entry_24xx *)ms_pkt)->comp_status);
		else
			comp_status = le16_to_cpu(ms_pkt->status);
		switch (comp_status) {
		case CS_COMPLETE:
		case CS_DATA_UNDERRUN:
		case CS_DATA_OVERRUN:		/* Overrun? */
			if (ct_rsp->header.response !=
			    cpu_to_be16(CT_ACCEPT_RESPONSE)) {
				ql_dbg(ql_dbg_disc + ql_dbg_buffer, vha, 0x2077,
				    "%s failed rejected request on port_id: %02x%02x%02x Completion status 0x%x, response 0x%x\n",
				    routine, vha->d_id.b.domain,
				    vha->d_id.b.area, vha->d_id.b.al_pa,
				    comp_status, ct_rsp->header.response);
				ql_dump_buffer(ql_dbg_disc + ql_dbg_buffer, vha,
				    0x2078, (uint8_t *)&ct_rsp->header,
				    sizeof(struct ct_rsp_hdr));
				rval = QLA_INVALID_COMMAND;
			} else
				rval = QLA_SUCCESS;
			break;
		case CS_PORT_LOGGED_OUT:
			if (IS_FWI2_CAPABLE(ha)) {
				if (le16_to_cpu(ms_pkt->loop_id.extended) ==
				    NPH_SNS)
					lid_is_sns = true;
			} else {
				if (le16_to_cpu(ms_pkt->loop_id.extended) ==
				    SIMPLE_NAME_SERVER)
					lid_is_sns = true;
			}
			if (lid_is_sns) {
				ql_dbg(ql_dbg_async, vha, 0x502b,
					"%s failed, Name server has logged out",
					routine);
				rval = QLA_NOT_LOGGED_IN;
				set_bit(LOOP_RESYNC_NEEDED, &vha->dpc_flags);
				set_bit(LOCAL_LOOP_UPDATE, &vha->dpc_flags);
			}
			break;
		case CS_TIMEOUT:
			rval = QLA_FUNCTION_TIMEOUT;
			/* fall through */
		default:
			ql_dbg(ql_dbg_disc, vha, 0x2033,
			    "%s failed, completion status (%x) on port_id: "
			    "%02x%02x%02x.\n", routine, comp_status,
			    vha->d_id.b.domain, vha->d_id.b.area,
			    vha->d_id.b.al_pa);
			break;
		}
	}
	return rval;
}