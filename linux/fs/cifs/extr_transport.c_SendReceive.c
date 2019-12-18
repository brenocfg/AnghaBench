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
struct smb_rqst {int rq_nvec; struct kvec* rq_iov; } ;
struct smb_hdr {int /*<<< orphan*/  smb_buf_length; } ;
struct mid_q_entry {scalar_t__ mid_state; int /*<<< orphan*/  resp_buf; int /*<<< orphan*/  callback; int /*<<< orphan*/  sequence_number; } ;
struct kvec {unsigned int iov_len; struct smb_hdr* iov_base; } ;
struct cifs_ses {struct TCP_Server_Info* server; } ;
struct cifs_credits {int value; int /*<<< orphan*/  instance; } ;
struct TCP_Server_Info {scalar_t__ tcpStatus; int sequence_number; int /*<<< orphan*/  srv_mutex; } ;

/* Variables and functions */
 int CIFSMaxBufSize ; 
 scalar_t__ CifsExiting ; 
 int /*<<< orphan*/  DeleteMidQEntry ; 
 int EIO ; 
 int ENOENT ; 
 int /*<<< orphan*/  GlobalMid_Lock ; 
 int MAX_CIFS_HDR_SIZE ; 
 scalar_t__ MID_REQUEST_SUBMITTED ; 
 scalar_t__ MID_RESPONSE_RECEIVED ; 
 int /*<<< orphan*/  VFS ; 
 int /*<<< orphan*/  add_credits (struct TCP_Server_Info*,struct cifs_credits*,int /*<<< orphan*/ ) ; 
 int allocate_mid (struct cifs_ses*,struct smb_hdr*,struct mid_q_entry**) ; 
 unsigned int be32_to_cpu (int /*<<< orphan*/ ) ; 
 int cifs_check_receive (struct mid_q_entry*,struct TCP_Server_Info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cifs_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  cifs_delete_mid (struct mid_q_entry*) ; 
 int /*<<< orphan*/  cifs_in_send_dec (struct TCP_Server_Info*) ; 
 int /*<<< orphan*/  cifs_in_send_inc (struct TCP_Server_Info*) ; 
 int /*<<< orphan*/  cifs_save_when_sent (struct mid_q_entry*) ; 
 int /*<<< orphan*/  cifs_server_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int cifs_sign_smb (struct smb_hdr*,struct TCP_Server_Info*,int /*<<< orphan*/ *) ; 
 int cifs_sync_mid_result (struct mid_q_entry*,struct TCP_Server_Info*) ; 
 int get_rfc1002_length (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct smb_hdr*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  send_cancel (struct TCP_Server_Info*,struct smb_rqst*,struct mid_q_entry*) ; 
 int smb_send (struct TCP_Server_Info*,struct smb_hdr*,unsigned int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int wait_for_free_request (struct TCP_Server_Info*,int const,int /*<<< orphan*/ *) ; 
 int wait_for_response (struct TCP_Server_Info*,struct mid_q_entry*) ; 

int
SendReceive(const unsigned int xid, struct cifs_ses *ses,
	    struct smb_hdr *in_buf, struct smb_hdr *out_buf,
	    int *pbytes_returned, const int flags)
{
	int rc = 0;
	struct mid_q_entry *midQ;
	unsigned int len = be32_to_cpu(in_buf->smb_buf_length);
	struct kvec iov = { .iov_base = in_buf, .iov_len = len };
	struct smb_rqst rqst = { .rq_iov = &iov, .rq_nvec = 1 };
	struct cifs_credits credits = { .value = 1, .instance = 0 };
	struct TCP_Server_Info *server;

	if (ses == NULL) {
		cifs_dbg(VFS, "Null smb session\n");
		return -EIO;
	}
	server = ses->server;
	if (server == NULL) {
		cifs_dbg(VFS, "Null tcp session\n");
		return -EIO;
	}

	if (server->tcpStatus == CifsExiting)
		return -ENOENT;

	/* Ensure that we do not send more than 50 overlapping requests
	   to the same server. We may make this configurable later or
	   use ses->maxReq */

	if (len > CIFSMaxBufSize + MAX_CIFS_HDR_SIZE - 4) {
		cifs_server_dbg(VFS, "Illegal length, greater than maximum frame, %d\n",
			 len);
		return -EIO;
	}

	rc = wait_for_free_request(server, flags, &credits.instance);
	if (rc)
		return rc;

	/* make sure that we sign in the same order that we send on this socket
	   and avoid races inside tcp sendmsg code that could cause corruption
	   of smb data */

	mutex_lock(&server->srv_mutex);

	rc = allocate_mid(ses, in_buf, &midQ);
	if (rc) {
		mutex_unlock(&ses->server->srv_mutex);
		/* Update # of requests on wire to server */
		add_credits(server, &credits, 0);
		return rc;
	}

	rc = cifs_sign_smb(in_buf, server, &midQ->sequence_number);
	if (rc) {
		mutex_unlock(&server->srv_mutex);
		goto out;
	}

	midQ->mid_state = MID_REQUEST_SUBMITTED;

	cifs_in_send_inc(server);
	rc = smb_send(server, in_buf, len);
	cifs_in_send_dec(server);
	cifs_save_when_sent(midQ);

	if (rc < 0)
		server->sequence_number -= 2;

	mutex_unlock(&server->srv_mutex);

	if (rc < 0)
		goto out;

	rc = wait_for_response(server, midQ);
	if (rc != 0) {
		send_cancel(server, &rqst, midQ);
		spin_lock(&GlobalMid_Lock);
		if (midQ->mid_state == MID_REQUEST_SUBMITTED) {
			/* no longer considered to be "in-flight" */
			midQ->callback = DeleteMidQEntry;
			spin_unlock(&GlobalMid_Lock);
			add_credits(server, &credits, 0);
			return rc;
		}
		spin_unlock(&GlobalMid_Lock);
	}

	rc = cifs_sync_mid_result(midQ, server);
	if (rc != 0) {
		add_credits(server, &credits, 0);
		return rc;
	}

	if (!midQ->resp_buf || !out_buf ||
	    midQ->mid_state != MID_RESPONSE_RECEIVED) {
		rc = -EIO;
		cifs_server_dbg(VFS, "Bad MID state?\n");
		goto out;
	}

	*pbytes_returned = get_rfc1002_length(midQ->resp_buf);
	memcpy(out_buf, midQ->resp_buf, *pbytes_returned + 4);
	rc = cifs_check_receive(midQ, server, 0);
out:
	cifs_delete_mid(midQ);
	add_credits(server, &credits, 0);

	return rc;
}