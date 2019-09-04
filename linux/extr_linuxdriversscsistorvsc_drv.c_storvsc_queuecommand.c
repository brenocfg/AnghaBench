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
typedef  int /*<<< orphan*/  u64 ;
typedef  int u32 ;
struct TYPE_6__ {int time_out_value; int srb_flags; int /*<<< orphan*/  queue_action; int /*<<< orphan*/  queue_tag; } ;
struct vmscsi_request {int /*<<< orphan*/  cdb_length; int /*<<< orphan*/  cdb; int /*<<< orphan*/  lun; int /*<<< orphan*/  target_id; int /*<<< orphan*/  path_id; int /*<<< orphan*/  port_number; TYPE_2__ win8_extension; int /*<<< orphan*/  data_in; } ;
struct TYPE_8__ {int len; int /*<<< orphan*/ * pfn_array; int /*<<< orphan*/  offset; } ;
struct vmbus_packet_mpb_array {TYPE_4__ range; } ;
struct TYPE_5__ {struct vmscsi_request vm_srb; } ;
struct storvsc_cmd_request {int payload_sz; struct vmbus_packet_mpb_array* payload; int /*<<< orphan*/  mpb; TYPE_1__ vstor_packet; struct scsi_cmnd* cmd; } ;
struct scsi_cmnd {int sc_data_direction; int /*<<< orphan*/  cmnd; int /*<<< orphan*/  cmd_len; TYPE_3__* device; int /*<<< orphan*/  (* scsi_done ) (struct scsi_cmnd*) ;} ;
struct scatterlist {int /*<<< orphan*/  offset; } ;
struct hv_host_device {int /*<<< orphan*/  port; struct hv_device* dev; } ;
struct hv_device {int dummy; } ;
struct Scsi_Host {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  lun; int /*<<< orphan*/  id; int /*<<< orphan*/  channel; scalar_t__ tagged_supported; } ;

/* Variables and functions */
#define  DMA_FROM_DEVICE 130 
#define  DMA_NONE 129 
#define  DMA_TO_DEVICE 128 
 int EAGAIN ; 
 int EINVAL ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 unsigned int MAX_PAGE_BUFFER_COUNT ; 
 int /*<<< orphan*/  READ_TYPE ; 
 int SCSI_MLQUEUE_DEVICE_BUSY ; 
 int /*<<< orphan*/  SP_UNTAGGED ; 
 int SRB_FLAGS_DATA_IN ; 
 int SRB_FLAGS_DATA_OUT ; 
 int SRB_FLAGS_DISABLE_SYNCH_TRANSFER ; 
 int SRB_FLAGS_NO_DATA_TRANSFER ; 
 int SRB_FLAGS_NO_QUEUE_FREEZE ; 
 int SRB_FLAGS_QUEUE_ACTION_ENABLE ; 
 int /*<<< orphan*/  SRB_SIMPLE_TAG_REQUEST ; 
 int /*<<< orphan*/  UNKNOWN_TYPE ; 
 scalar_t__ VMSTOR_PROTO_VERSION_WIN8 ; 
 int /*<<< orphan*/  WARN (int,char*,int) ; 
 int /*<<< orphan*/  WRITE_TYPE ; 
 int /*<<< orphan*/  get_cpu () ; 
 int /*<<< orphan*/  kfree (struct vmbus_packet_mpb_array*) ; 
 struct vmbus_packet_mpb_array* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  page_to_pfn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_cpu () ; 
 int scsi_bufflen (struct scsi_cmnd*) ; 
 struct storvsc_cmd_request* scsi_cmd_priv (struct scsi_cmnd*) ; 
 unsigned int scsi_sg_count (struct scsi_cmnd*) ; 
 scalar_t__ scsi_sglist (struct scsi_cmnd*) ; 
 struct scatterlist* sg_next (struct scatterlist*) ; 
 int /*<<< orphan*/  sg_page (struct scatterlist*) ; 
 struct hv_host_device* shost_priv (struct Scsi_Host*) ; 
 int storvsc_do_io (struct hv_device*,struct storvsc_cmd_request*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  storvsc_scsi_cmd_ok (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  stub1 (struct scsi_cmnd*) ; 
 scalar_t__ vmstor_proto_version ; 

__attribute__((used)) static int storvsc_queuecommand(struct Scsi_Host *host, struct scsi_cmnd *scmnd)
{
	int ret;
	struct hv_host_device *host_dev = shost_priv(host);
	struct hv_device *dev = host_dev->dev;
	struct storvsc_cmd_request *cmd_request = scsi_cmd_priv(scmnd);
	int i;
	struct scatterlist *sgl;
	unsigned int sg_count = 0;
	struct vmscsi_request *vm_srb;
	struct scatterlist *cur_sgl;
	struct vmbus_packet_mpb_array  *payload;
	u32 payload_sz;
	u32 length;

	if (vmstor_proto_version <= VMSTOR_PROTO_VERSION_WIN8) {
		/*
		 * On legacy hosts filter unimplemented commands.
		 * Future hosts are expected to correctly handle
		 * unsupported commands. Furthermore, it is
		 * possible that some of the currently
		 * unsupported commands maybe supported in
		 * future versions of the host.
		 */
		if (!storvsc_scsi_cmd_ok(scmnd)) {
			scmnd->scsi_done(scmnd);
			return 0;
		}
	}

	/* Setup the cmd request */
	cmd_request->cmd = scmnd;

	vm_srb = &cmd_request->vstor_packet.vm_srb;
	vm_srb->win8_extension.time_out_value = 60;

	vm_srb->win8_extension.srb_flags |=
		SRB_FLAGS_DISABLE_SYNCH_TRANSFER;

	if (scmnd->device->tagged_supported) {
		vm_srb->win8_extension.srb_flags |=
		(SRB_FLAGS_QUEUE_ACTION_ENABLE | SRB_FLAGS_NO_QUEUE_FREEZE);
		vm_srb->win8_extension.queue_tag = SP_UNTAGGED;
		vm_srb->win8_extension.queue_action = SRB_SIMPLE_TAG_REQUEST;
	}

	/* Build the SRB */
	switch (scmnd->sc_data_direction) {
	case DMA_TO_DEVICE:
		vm_srb->data_in = WRITE_TYPE;
		vm_srb->win8_extension.srb_flags |= SRB_FLAGS_DATA_OUT;
		break;
	case DMA_FROM_DEVICE:
		vm_srb->data_in = READ_TYPE;
		vm_srb->win8_extension.srb_flags |= SRB_FLAGS_DATA_IN;
		break;
	case DMA_NONE:
		vm_srb->data_in = UNKNOWN_TYPE;
		vm_srb->win8_extension.srb_flags |= SRB_FLAGS_NO_DATA_TRANSFER;
		break;
	default:
		/*
		 * This is DMA_BIDIRECTIONAL or something else we are never
		 * supposed to see here.
		 */
		WARN(1, "Unexpected data direction: %d\n",
		     scmnd->sc_data_direction);
		return -EINVAL;
	}


	vm_srb->port_number = host_dev->port;
	vm_srb->path_id = scmnd->device->channel;
	vm_srb->target_id = scmnd->device->id;
	vm_srb->lun = scmnd->device->lun;

	vm_srb->cdb_length = scmnd->cmd_len;

	memcpy(vm_srb->cdb, scmnd->cmnd, vm_srb->cdb_length);

	sgl = (struct scatterlist *)scsi_sglist(scmnd);
	sg_count = scsi_sg_count(scmnd);

	length = scsi_bufflen(scmnd);
	payload = (struct vmbus_packet_mpb_array *)&cmd_request->mpb;
	payload_sz = sizeof(cmd_request->mpb);

	if (sg_count) {
		if (sg_count > MAX_PAGE_BUFFER_COUNT) {

			payload_sz = (sg_count * sizeof(u64) +
				      sizeof(struct vmbus_packet_mpb_array));
			payload = kzalloc(payload_sz, GFP_ATOMIC);
			if (!payload)
				return SCSI_MLQUEUE_DEVICE_BUSY;
		}

		payload->range.len = length;
		payload->range.offset = sgl[0].offset;

		cur_sgl = sgl;
		for (i = 0; i < sg_count; i++) {
			payload->range.pfn_array[i] =
				page_to_pfn(sg_page((cur_sgl)));
			cur_sgl = sg_next(cur_sgl);
		}
	}

	cmd_request->payload = payload;
	cmd_request->payload_sz = payload_sz;

	/* Invokes the vsc to start an IO */
	ret = storvsc_do_io(dev, cmd_request, get_cpu());
	put_cpu();

	if (ret == -EAGAIN) {
		if (payload_sz > sizeof(cmd_request->mpb))
			kfree(payload);
		/* no more space */
		return SCSI_MLQUEUE_DEVICE_BUSY;
	}

	return 0;
}