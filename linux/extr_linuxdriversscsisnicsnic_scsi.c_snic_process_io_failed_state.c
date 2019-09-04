#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct snic_icmnd_cmpl {int scsi_status; int /*<<< orphan*/  resid; } ;
struct TYPE_7__ {int /*<<< orphan*/  scsi_errs; int /*<<< orphan*/  io_errs; int /*<<< orphan*/  out_of_res; } ;
struct TYPE_6__ {int /*<<< orphan*/  sgl_inval; int /*<<< orphan*/  data_cnt_mismat; int /*<<< orphan*/  io_aborted; int /*<<< orphan*/  io_tmo; } ;
struct TYPE_5__ {int /*<<< orphan*/  io_not_found; } ;
struct TYPE_8__ {TYPE_3__ fw; TYPE_2__ misc; TYPE_1__ io; } ;
struct snic {int /*<<< orphan*/  shost; TYPE_4__ s_stats; } ;
struct scsi_cmnd {int result; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_FLAGS (struct scsi_cmnd*) ; 
 int DID_ABORT ; 
 int DID_ERROR ; 
 int DID_NO_CONNECT ; 
 int DID_REQUEUE ; 
 int DID_TIME_OUT ; 
 int /*<<< orphan*/  SNIC_HOST_ERR (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SNIC_SCSI_DBG (int /*<<< orphan*/ ,char*) ; 
#define  SNIC_STAT_ABORTED 142 
#define  SNIC_STAT_CMND_REJECT 141 
#define  SNIC_STAT_DATA_CNT_MISMATCH 140 
#define  SNIC_STAT_DEV_OFFLINE 139 
#define  SNIC_STAT_FATAL_ERROR 138 
#define  SNIC_STAT_FW_ERR 137 
#define  SNIC_STAT_INVALID_HDR 136 
#define  SNIC_STAT_INVALID_PARM 135 
#define  SNIC_STAT_IO_NOT_FOUND 134 
#define  SNIC_STAT_NOT_READY 133 
#define  SNIC_STAT_OUT_OF_RES 132 
#define  SNIC_STAT_REQ_NOT_SUP 131 
#define  SNIC_STAT_SCSI_ERR 130 
#define  SNIC_STAT_SGL_INVALID 129 
#define  SNIC_STAT_TIMEOUT 128 
 int /*<<< orphan*/  atomic64_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_set_resid (struct scsi_cmnd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snic_io_status_to_str (int) ; 

__attribute__((used)) static void
snic_process_io_failed_state(struct snic *snic,
			     struct snic_icmnd_cmpl *icmnd_cmpl,
			     struct scsi_cmnd *sc,
			     u8 cmpl_stat)
{
	int res = 0;

	switch (cmpl_stat) {
	case SNIC_STAT_TIMEOUT:		/* Req was timedout */
		atomic64_inc(&snic->s_stats.misc.io_tmo);
		res = DID_TIME_OUT;
		break;

	case SNIC_STAT_ABORTED:		/* Req was aborted */
		atomic64_inc(&snic->s_stats.misc.io_aborted);
		res = DID_ABORT;
		break;

	case SNIC_STAT_DATA_CNT_MISMATCH:/* Recv/Sent more/less data than exp */
		atomic64_inc(&snic->s_stats.misc.data_cnt_mismat);
		scsi_set_resid(sc, le32_to_cpu(icmnd_cmpl->resid));
		res = DID_ERROR;
		break;

	case SNIC_STAT_OUT_OF_RES: /* Out of resources to complete request */
		atomic64_inc(&snic->s_stats.fw.out_of_res);
		res = DID_REQUEUE;
		break;

	case SNIC_STAT_IO_NOT_FOUND:	/* Requested I/O was not found */
		atomic64_inc(&snic->s_stats.io.io_not_found);
		res = DID_ERROR;
		break;

	case SNIC_STAT_SGL_INVALID:	/* Req was aborted to due to sgl error*/
		atomic64_inc(&snic->s_stats.misc.sgl_inval);
		res = DID_ERROR;
		break;

	case SNIC_STAT_FW_ERR:		/* Req terminated due to FW Error */
		atomic64_inc(&snic->s_stats.fw.io_errs);
		res = DID_ERROR;
		break;

	case SNIC_STAT_SCSI_ERR:	/* FW hits SCSI Error */
		atomic64_inc(&snic->s_stats.fw.scsi_errs);
		break;

	case SNIC_STAT_NOT_READY:	/* XPT yet to initialize */
	case SNIC_STAT_DEV_OFFLINE:	/* Device offline */
		res = DID_NO_CONNECT;
		break;

	case SNIC_STAT_INVALID_HDR:	/* Hdr contains invalid data */
	case SNIC_STAT_INVALID_PARM:	/* Some param in req is invalid */
	case SNIC_STAT_REQ_NOT_SUP:	/* Req type is not supported */
	case SNIC_STAT_CMND_REJECT:	/* Req rejected */
	case SNIC_STAT_FATAL_ERROR:	/* XPT Error */
	default:
		SNIC_SCSI_DBG(snic->shost,
			      "Invalid Hdr/Param or Req Not Supported or Cmnd Rejected or Device Offline. or Unknown\n");
		res = DID_ERROR;
		break;
	}

	SNIC_HOST_ERR(snic->shost, "fw returns failed status %s flags 0x%llx\n",
		      snic_io_status_to_str(cmpl_stat), CMD_FLAGS(sc));

	/* Set sc->result */
	sc->result = (res << 16) | icmnd_cmpl->scsi_status;
}