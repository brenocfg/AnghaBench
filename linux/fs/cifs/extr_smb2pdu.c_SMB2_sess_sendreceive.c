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
struct smb_rqst {int rq_nvec; TYPE_1__* rq_iov; } ;
struct smb2_sess_setup_req {void* SecurityBufferLength; void* SecurityBufferOffset; } ;
struct kvec {int /*<<< orphan*/  member_1; int /*<<< orphan*/ * member_0; } ;
struct SMB2_sess_data {TYPE_1__* iov; int /*<<< orphan*/  buf0_type; int /*<<< orphan*/  ses; int /*<<< orphan*/  xid; } ;
struct TYPE_2__ {int iov_len; struct smb2_sess_setup_req* iov_base; } ;

/* Variables and functions */
 int CIFS_LOG_ERROR ; 
 int CIFS_NEG_OP ; 
 int cifs_send_recv (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct smb_rqst*,int /*<<< orphan*/ *,int,struct kvec*) ; 
 int /*<<< orphan*/  cifs_small_buf_release (struct smb2_sess_setup_req*) ; 
 void* cpu_to_le16 (int) ; 
 int /*<<< orphan*/  memcpy (TYPE_1__*,struct kvec*,int) ; 
 int /*<<< orphan*/  memset (struct smb_rqst*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
SMB2_sess_sendreceive(struct SMB2_sess_data *sess_data)
{
	int rc;
	struct smb_rqst rqst;
	struct smb2_sess_setup_req *req = sess_data->iov[0].iov_base;
	struct kvec rsp_iov = { NULL, 0 };

	/* Testing shows that buffer offset must be at location of Buffer[0] */
	req->SecurityBufferOffset =
		cpu_to_le16(sizeof(struct smb2_sess_setup_req) - 1 /* pad */);
	req->SecurityBufferLength = cpu_to_le16(sess_data->iov[1].iov_len);

	memset(&rqst, 0, sizeof(struct smb_rqst));
	rqst.rq_iov = sess_data->iov;
	rqst.rq_nvec = 2;

	/* BB add code to build os and lm fields */
	rc = cifs_send_recv(sess_data->xid, sess_data->ses,
			    &rqst,
			    &sess_data->buf0_type,
			    CIFS_LOG_ERROR | CIFS_NEG_OP, &rsp_iov);
	cifs_small_buf_release(sess_data->iov[0].iov_base);
	memcpy(&sess_data->iov[0], &rsp_iov, sizeof(struct kvec));

	return rc;
}