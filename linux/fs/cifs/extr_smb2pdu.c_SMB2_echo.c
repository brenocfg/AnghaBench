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
struct smb_rqst {int rq_nvec; struct kvec* rq_iov; } ;
struct TYPE_2__ {int /*<<< orphan*/  CreditRequest; } ;
struct smb2_echo_req {TYPE_1__ sync_hdr; } ;
struct kvec {unsigned int iov_len; char* iov_base; } ;
struct TCP_Server_Info {scalar_t__ tcpStatus; int /*<<< orphan*/  reconnect; } ;

/* Variables and functions */
 int /*<<< orphan*/  CIFS_ECHO_OP ; 
 scalar_t__ CifsNeedNegotiate ; 
 int /*<<< orphan*/  FYI ; 
 int /*<<< orphan*/  SMB2_ECHO ; 
 int cifs_call_async (struct TCP_Server_Info*,struct smb_rqst*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct TCP_Server_Info*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cifs_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  cifs_small_buf_release (struct smb2_echo_req*) ; 
 int /*<<< orphan*/  cifsiod_wq ; 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smb2_echo_callback ; 
 int smb2_plain_req_init (int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**,unsigned int*) ; 

int
SMB2_echo(struct TCP_Server_Info *server)
{
	struct smb2_echo_req *req;
	int rc = 0;
	struct kvec iov[1];
	struct smb_rqst rqst = { .rq_iov = iov,
				 .rq_nvec = 1 };
	unsigned int total_len;

	cifs_dbg(FYI, "In echo request\n");

	if (server->tcpStatus == CifsNeedNegotiate) {
		/* No need to send echo on newly established connections */
		queue_delayed_work(cifsiod_wq, &server->reconnect, 0);
		return rc;
	}

	rc = smb2_plain_req_init(SMB2_ECHO, NULL, (void **)&req, &total_len);
	if (rc)
		return rc;

	req->sync_hdr.CreditRequest = cpu_to_le16(1);

	iov[0].iov_len = total_len;
	iov[0].iov_base = (char *)req;

	rc = cifs_call_async(server, &rqst, NULL, smb2_echo_callback, NULL,
			     server, CIFS_ECHO_OP, NULL);
	if (rc)
		cifs_dbg(FYI, "Echo request failed: %d\n", rc);

	cifs_small_buf_release(req);
	return rc;
}