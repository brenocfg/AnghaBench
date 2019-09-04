#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ulong ;
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct snic_async_evnotify {int /*<<< orphan*/  ev_id; } ;
struct TYPE_2__ {struct snic_async_evnotify async_ev; } ;
struct snic_fw_req {int /*<<< orphan*/  hdr; TYPE_1__ u; } ;
struct snic {int /*<<< orphan*/  shost; } ;

/* Variables and functions */
 int /*<<< orphan*/  SNIC_ASSERT_NOT_IMPL (int) ; 
 int /*<<< orphan*/  SNIC_BUG_ON (int) ; 
#define  SNIC_EV_CONF_CHG 137 
#define  SNIC_EV_DISC_CMPL 136 
#define  SNIC_EV_LUN_ADDED 135 
#define  SNIC_EV_LUN_DELTD 134 
#define  SNIC_EV_LUN_OFFLINE 133 
#define  SNIC_EV_LUN_ONLINE 132 
#define  SNIC_EV_TGT_ADDED 131 
#define  SNIC_EV_TGT_DELTD 130 
#define  SNIC_EV_TGT_OFFLINE 129 
#define  SNIC_EV_TGT_ONLINE 128 
 int /*<<< orphan*/  SNIC_HOST_INFO (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SNIC_SCSI_DBG (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snic_io_hdr_dec (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*,int*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
snic_aen_handler(struct snic *snic, struct snic_fw_req *fwreq)
{
	u8 typ, hdr_stat;
	u32 cmnd_id, hid;
	ulong ctx;
	struct snic_async_evnotify *aen = &fwreq->u.async_ev;
	u32 event_id = 0;

	snic_io_hdr_dec(&fwreq->hdr, &typ, &hdr_stat, &cmnd_id, &hid, &ctx);
	SNIC_SCSI_DBG(snic->shost,
		      "aen: type = %x, hdr_stat = %x, cmnd_id = %x, hid = %x, ctx = %lx\n",
		      typ, hdr_stat, cmnd_id, hid, ctx);

	event_id = le32_to_cpu(aen->ev_id);

	switch (event_id) {
	case SNIC_EV_TGT_OFFLINE:
		SNIC_HOST_INFO(snic->shost, "aen:TGT_OFFLINE Event Recvd.\n");
		break;

	case SNIC_EV_TGT_ONLINE:
		SNIC_HOST_INFO(snic->shost, "aen:TGT_ONLINE Event Recvd.\n");
		break;

	case SNIC_EV_LUN_OFFLINE:
		SNIC_HOST_INFO(snic->shost, "aen:LUN_OFFLINE Event Recvd.\n");
		break;

	case SNIC_EV_LUN_ONLINE:
		SNIC_HOST_INFO(snic->shost, "aen:LUN_ONLINE Event Recvd.\n");
		break;

	case SNIC_EV_CONF_CHG:
		SNIC_HOST_INFO(snic->shost, "aen:Config Change Event Recvd.\n");
		break;

	case SNIC_EV_TGT_ADDED:
		SNIC_HOST_INFO(snic->shost, "aen:TGT_ADD Event Recvd.\n");
		break;

	case SNIC_EV_TGT_DELTD:
		SNIC_HOST_INFO(snic->shost, "aen:TGT_DEL Event Recvd.\n");
		break;

	case SNIC_EV_LUN_ADDED:
		SNIC_HOST_INFO(snic->shost, "aen:LUN_ADD Event Recvd.\n");
		break;

	case SNIC_EV_LUN_DELTD:
		SNIC_HOST_INFO(snic->shost, "aen:LUN_DEL Event Recvd.\n");
		break;

	case SNIC_EV_DISC_CMPL:
		SNIC_HOST_INFO(snic->shost, "aen:DISC_CMPL Event Recvd.\n");
		break;

	default:
		SNIC_HOST_INFO(snic->shost, "aen:Unknown Event Recvd.\n");
		SNIC_BUG_ON(1);
		break;
	}

	SNIC_ASSERT_NOT_IMPL(1);
}