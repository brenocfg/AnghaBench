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
struct TYPE_3__ {int /*<<< orphan*/  CreditRequest; scalar_t__ SessionId; } ;
struct smb2_sess_setup_req {scalar_t__ Channel; scalar_t__ Capabilities; scalar_t__ SecurityMode; TYPE_1__ sync_hdr; scalar_t__ Flags; int /*<<< orphan*/  PreviousSessionId; } ;
struct cifs_ses {struct TCP_Server_Info* server; } ;
struct TCP_Server_Info {scalar_t__ sign; } ;
struct SMB2_sess_data {int /*<<< orphan*/  buf0_type; TYPE_2__* iov; int /*<<< orphan*/  previous_session; struct cifs_ses* ses; } ;
struct TYPE_4__ {char* iov_base; unsigned int iov_len; } ;

/* Variables and functions */
 int CIFSSEC_MAY_SIGN ; 
 int /*<<< orphan*/  CIFS_SMALL_BUFFER ; 
 int /*<<< orphan*/  SMB2_GLOBAL_CAP_DFS ; 
 scalar_t__ SMB2_NEGOTIATE_SIGNING_ENABLED ; 
 scalar_t__ SMB2_NEGOTIATE_SIGNING_REQUIRED ; 
 int /*<<< orphan*/  SMB2_SESSION_SETUP ; 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 scalar_t__ cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int global_secflags ; 
 int smb2_plain_req_init (int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**,unsigned int*) ; 

__attribute__((used)) static int
SMB2_sess_alloc_buffer(struct SMB2_sess_data *sess_data)
{
	int rc;
	struct cifs_ses *ses = sess_data->ses;
	struct smb2_sess_setup_req *req;
	struct TCP_Server_Info *server = ses->server;
	unsigned int total_len;

	rc = smb2_plain_req_init(SMB2_SESSION_SETUP, NULL, (void **) &req,
			     &total_len);
	if (rc)
		return rc;

	/* First session, not a reauthenticate */
	req->sync_hdr.SessionId = 0;

	/* if reconnect, we need to send previous sess id, otherwise it is 0 */
	req->PreviousSessionId = sess_data->previous_session;

	req->Flags = 0; /* MBZ */

	/* enough to enable echos and oplocks and one max size write */
	req->sync_hdr.CreditRequest = cpu_to_le16(130);

	/* only one of SMB2 signing flags may be set in SMB2 request */
	if (server->sign)
		req->SecurityMode = SMB2_NEGOTIATE_SIGNING_REQUIRED;
	else if (global_secflags & CIFSSEC_MAY_SIGN) /* one flag unlike MUST_ */
		req->SecurityMode = SMB2_NEGOTIATE_SIGNING_ENABLED;
	else
		req->SecurityMode = 0;

#ifdef CONFIG_CIFS_DFS_UPCALL
	req->Capabilities = cpu_to_le32(SMB2_GLOBAL_CAP_DFS);
#else
	req->Capabilities = 0;
#endif /* DFS_UPCALL */

	req->Channel = 0; /* MBZ */

	sess_data->iov[0].iov_base = (char *)req;
	/* 1 for pad */
	sess_data->iov[0].iov_len = total_len - 1;
	/*
	 * This variable will be used to clear the buffer
	 * allocated above in case of any error in the calling function.
	 */
	sess_data->buf0_type = CIFS_SMALL_BUFFER;

	return 0;
}