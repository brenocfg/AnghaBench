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
struct smb2_sync_hdr {int SessionId; int TreeId; int /*<<< orphan*/  Flags; void* NextCommand; void* ProcessId; } ;
struct smb2_read_plain_req {int PersistentFileId; int VolatileFileId; void* RemainingBytes; int /*<<< orphan*/  Offset; void* Length; scalar_t__ MinimumCount; scalar_t__ Channel; scalar_t__ ReadChannelInfoLength; scalar_t__ ReadChannelInfoOffset; struct smb2_sync_hdr sync_hdr; } ;
struct cifs_readdata {int dummy; } ;
struct cifs_io_parms {unsigned int pid; int persistent_fid; int volatile_fid; unsigned int length; int /*<<< orphan*/  offset; TYPE_2__* tcon; } ;
struct TCP_Server_Info {int dummy; } ;
struct TYPE_4__ {TYPE_1__* ses; } ;
struct TYPE_3__ {struct TCP_Server_Info* server; } ;

/* Variables and functions */
 int CHAINED_REQUEST ; 
 int DIV_ROUND_UP (unsigned int,int) ; 
 int EACCES ; 
 int ECONNABORTED ; 
 int END_OF_CHAIN ; 
 int RELATED_REQUEST ; 
 int /*<<< orphan*/  SMB2_FLAGS_RELATED_OPERATIONS ; 
 int /*<<< orphan*/  SMB2_READ ; 
 void* cpu_to_le32 (unsigned int) ; 
 int /*<<< orphan*/  cpu_to_le64 (int /*<<< orphan*/ ) ; 
 int smb2_plain_req_init (int /*<<< orphan*/ ,TYPE_2__*,void**,unsigned int*) ; 

__attribute__((used)) static int
smb2_new_read_req(void **buf, unsigned int *total_len,
	struct cifs_io_parms *io_parms, struct cifs_readdata *rdata,
	unsigned int remaining_bytes, int request_type)
{
	int rc = -EACCES;
	struct smb2_read_plain_req *req = NULL;
	struct smb2_sync_hdr *shdr;
	struct TCP_Server_Info *server;

	rc = smb2_plain_req_init(SMB2_READ, io_parms->tcon, (void **) &req,
				 total_len);
	if (rc)
		return rc;

	server = io_parms->tcon->ses->server;
	if (server == NULL)
		return -ECONNABORTED;

	shdr = &req->sync_hdr;
	shdr->ProcessId = cpu_to_le32(io_parms->pid);

	req->PersistentFileId = io_parms->persistent_fid;
	req->VolatileFileId = io_parms->volatile_fid;
	req->ReadChannelInfoOffset = 0; /* reserved */
	req->ReadChannelInfoLength = 0; /* reserved */
	req->Channel = 0; /* reserved */
	req->MinimumCount = 0;
	req->Length = cpu_to_le32(io_parms->length);
	req->Offset = cpu_to_le64(io_parms->offset);
#ifdef CONFIG_CIFS_SMB_DIRECT
	/*
	 * If we want to do a RDMA write, fill in and append
	 * smbd_buffer_descriptor_v1 to the end of read request
	 */
	if (server->rdma && rdata && !server->sign &&
		rdata->bytes >= server->smbd_conn->rdma_readwrite_threshold) {

		struct smbd_buffer_descriptor_v1 *v1;
		bool need_invalidate =
			io_parms->tcon->ses->server->dialect == SMB30_PROT_ID;

		rdata->mr = smbd_register_mr(
				server->smbd_conn, rdata->pages,
				rdata->nr_pages, rdata->page_offset,
				rdata->tailsz, true, need_invalidate);
		if (!rdata->mr)
			return -ENOBUFS;

		req->Channel = SMB2_CHANNEL_RDMA_V1_INVALIDATE;
		if (need_invalidate)
			req->Channel = SMB2_CHANNEL_RDMA_V1;
		req->ReadChannelInfoOffset =
			cpu_to_le16(offsetof(struct smb2_read_plain_req, Buffer));
		req->ReadChannelInfoLength =
			cpu_to_le16(sizeof(struct smbd_buffer_descriptor_v1));
		v1 = (struct smbd_buffer_descriptor_v1 *) &req->Buffer[0];
		v1->offset = cpu_to_le64(rdata->mr->mr->iova);
		v1->token = cpu_to_le32(rdata->mr->mr->rkey);
		v1->length = cpu_to_le32(rdata->mr->mr->length);

		*total_len += sizeof(*v1) - 1;
	}
#endif
	if (request_type & CHAINED_REQUEST) {
		if (!(request_type & END_OF_CHAIN)) {
			/* next 8-byte aligned request */
			*total_len = DIV_ROUND_UP(*total_len, 8) * 8;
			shdr->NextCommand = cpu_to_le32(*total_len);
		} else /* END_OF_CHAIN */
			shdr->NextCommand = 0;
		if (request_type & RELATED_REQUEST) {
			shdr->Flags |= SMB2_FLAGS_RELATED_OPERATIONS;
			/*
			 * Related requests use info from previous read request
			 * in chain.
			 */
			shdr->SessionId = 0xFFFFFFFF;
			shdr->TreeId = 0xFFFFFFFF;
			req->PersistentFileId = 0xFFFFFFFF;
			req->VolatileFileId = 0xFFFFFFFF;
		}
	}
	if (remaining_bytes > io_parms->length)
		req->RemainingBytes = cpu_to_le32(remaining_bytes);
	else
		req->RemainingBytes = 0;

	*buf = req;
	return rc;
}