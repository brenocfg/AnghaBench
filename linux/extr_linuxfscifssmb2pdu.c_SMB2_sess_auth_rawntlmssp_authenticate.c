#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_6__ {int /*<<< orphan*/  SessionId; } ;
struct smb2_sess_setup_rsp {int /*<<< orphan*/  SessionFlags; TYPE_3__ sync_hdr; } ;
struct TYPE_4__ {int /*<<< orphan*/  SessionId; } ;
struct smb2_sess_setup_req {TYPE_1__ sync_hdr; } ;
struct cifs_ses {unsigned char* ntlmssp; int /*<<< orphan*/  session_flags; int /*<<< orphan*/  Suid; } ;
struct SMB2_sess_data {int result; int /*<<< orphan*/ * func; TYPE_2__* iov; int /*<<< orphan*/  nls_cp; struct cifs_ses* ses; } ;
struct TYPE_5__ {unsigned char* iov_base; int /*<<< orphan*/  iov_len; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  FYI ; 
 int SMB2_sess_alloc_buffer (struct SMB2_sess_data*) ; 
 int SMB2_sess_establish_session (struct SMB2_sess_data*) ; 
 int /*<<< orphan*/  SMB2_sess_free_buffer (struct SMB2_sess_data*) ; 
 int SMB2_sess_sendreceive (struct SMB2_sess_data*) ; 
 int /*<<< orphan*/  VFS ; 
 int build_ntlmssp_auth_blob (unsigned char**,int /*<<< orphan*/ *,struct cifs_ses*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cifs_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  kfree (unsigned char*) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
SMB2_sess_auth_rawntlmssp_authenticate(struct SMB2_sess_data *sess_data)
{
	int rc;
	struct cifs_ses *ses = sess_data->ses;
	struct smb2_sess_setup_req *req;
	struct smb2_sess_setup_rsp *rsp = NULL;
	unsigned char *ntlmssp_blob = NULL;
	bool use_spnego = false; /* else use raw ntlmssp */
	u16 blob_length = 0;

	rc = SMB2_sess_alloc_buffer(sess_data);
	if (rc)
		goto out;

	req = (struct smb2_sess_setup_req *) sess_data->iov[0].iov_base;
	req->sync_hdr.SessionId = ses->Suid;

	rc = build_ntlmssp_auth_blob(&ntlmssp_blob, &blob_length, ses,
					sess_data->nls_cp);
	if (rc) {
		cifs_dbg(FYI, "build_ntlmssp_auth_blob failed %d\n", rc);
		goto out;
	}

	if (use_spnego) {
		/* BB eventually need to add this */
		cifs_dbg(VFS, "spnego not supported for SMB2 yet\n");
		rc = -EOPNOTSUPP;
		goto out;
	}
	sess_data->iov[1].iov_base = ntlmssp_blob;
	sess_data->iov[1].iov_len = blob_length;

	rc = SMB2_sess_sendreceive(sess_data);
	if (rc)
		goto out;

	rsp = (struct smb2_sess_setup_rsp *)sess_data->iov[0].iov_base;

	ses->Suid = rsp->sync_hdr.SessionId;
	ses->session_flags = le16_to_cpu(rsp->SessionFlags);

	rc = SMB2_sess_establish_session(sess_data);
out:
	kfree(ntlmssp_blob);
	SMB2_sess_free_buffer(sess_data);
	kfree(ses->ntlmssp);
	ses->ntlmssp = NULL;
	sess_data->result = rc;
	sess_data->func = NULL;
}