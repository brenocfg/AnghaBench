#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct smb_hdr {int Uid; int WordCount; int Flags2; } ;
struct sess_data {int result; int /*<<< orphan*/ * func; int /*<<< orphan*/  nls_cp; TYPE_2__* iov; struct cifs_ses* ses; } ;
struct TYPE_9__ {unsigned char* response; } ;
struct cifs_ses {int Suid; unsigned char* ntlmssp; TYPE_4__ auth_key; } ;
typedef  int __u16 ;
struct TYPE_8__ {int /*<<< orphan*/  SecurityBlobLength; int /*<<< orphan*/  Action; } ;
struct TYPE_6__ {int /*<<< orphan*/  SecurityBlobLength; } ;
struct TYPE_10__ {TYPE_3__ resp; TYPE_1__ req; } ;
struct TYPE_7__ {unsigned char* iov_base; int iov_len; } ;
typedef  TYPE_5__ SESSION_SETUP_ANDX ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int /*<<< orphan*/  FYI ; 
 int GUEST_LOGIN ; 
 int SMBFLG2_UNICODE ; 
 int /*<<< orphan*/  VFS ; 
 int _sess_auth_rawntlmssp_assemble_req (struct sess_data*) ; 
 int build_ntlmssp_auth_blob (unsigned char**,int*,struct cifs_ses*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cifs_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 int /*<<< orphan*/  decode_ascii_ssetup (char**,int,struct cifs_ses*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  decode_unicode_ssetup (char**,int,struct cifs_ses*,int /*<<< orphan*/ ) ; 
 int get_bcc (struct smb_hdr*) ; 
 int /*<<< orphan*/  kfree (unsigned char*) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 char* pByteArea (struct smb_hdr*) ; 
 int sess_alloc_buffer (struct sess_data*,int) ; 
 int sess_establish_session (struct sess_data*) ; 
 int /*<<< orphan*/  sess_free_buffer (struct sess_data*) ; 
 int sess_sendreceive (struct sess_data*) ; 

__attribute__((used)) static void
sess_auth_rawntlmssp_authenticate(struct sess_data *sess_data)
{
	int rc;
	struct smb_hdr *smb_buf;
	SESSION_SETUP_ANDX *pSMB;
	struct cifs_ses *ses = sess_data->ses;
	__u16 bytes_remaining;
	char *bcc_ptr;
	unsigned char *ntlmsspblob = NULL;
	u16 blob_len;

	cifs_dbg(FYI, "rawntlmssp session setup authenticate phase\n");

	/* wct = 12 */
	rc = sess_alloc_buffer(sess_data, 12);
	if (rc)
		goto out;

	/* Build security blob before we assemble the request */
	pSMB = (SESSION_SETUP_ANDX *)sess_data->iov[0].iov_base;
	smb_buf = (struct smb_hdr *)pSMB;
	rc = build_ntlmssp_auth_blob(&ntlmsspblob,
					&blob_len, ses, sess_data->nls_cp);
	if (rc)
		goto out_free_ntlmsspblob;
	sess_data->iov[1].iov_len = blob_len;
	sess_data->iov[1].iov_base = ntlmsspblob;
	pSMB->req.SecurityBlobLength = cpu_to_le16(blob_len);
	/*
	 * Make sure that we tell the server that we are using
	 * the uid that it just gave us back on the response
	 * (challenge)
	 */
	smb_buf->Uid = ses->Suid;

	rc = _sess_auth_rawntlmssp_assemble_req(sess_data);
	if (rc)
		goto out_free_ntlmsspblob;

	rc = sess_sendreceive(sess_data);
	if (rc)
		goto out_free_ntlmsspblob;

	pSMB = (SESSION_SETUP_ANDX *)sess_data->iov[0].iov_base;
	smb_buf = (struct smb_hdr *)sess_data->iov[0].iov_base;
	if (smb_buf->WordCount != 4) {
		rc = -EIO;
		cifs_dbg(VFS, "bad word count %d\n", smb_buf->WordCount);
		goto out_free_ntlmsspblob;
	}

	if (le16_to_cpu(pSMB->resp.Action) & GUEST_LOGIN)
		cifs_dbg(FYI, "Guest login\n"); /* BB mark SesInfo struct? */

	if (ses->Suid != smb_buf->Uid) {
		ses->Suid = smb_buf->Uid;
		cifs_dbg(FYI, "UID changed! new UID = %llu\n", ses->Suid);
	}

	bytes_remaining = get_bcc(smb_buf);
	bcc_ptr = pByteArea(smb_buf);
	blob_len = le16_to_cpu(pSMB->resp.SecurityBlobLength);
	if (blob_len > bytes_remaining) {
		cifs_dbg(VFS, "bad security blob length %d\n",
				blob_len);
		rc = -EINVAL;
		goto out_free_ntlmsspblob;
	}
	bcc_ptr += blob_len;
	bytes_remaining -= blob_len;


	/* BB check if Unicode and decode strings */
	if (bytes_remaining == 0) {
		/* no string area to decode, do nothing */
	} else if (smb_buf->Flags2 & SMBFLG2_UNICODE) {
		/* unicode string area must be word-aligned */
		if (((unsigned long) bcc_ptr - (unsigned long) smb_buf) % 2) {
			++bcc_ptr;
			--bytes_remaining;
		}
		decode_unicode_ssetup(&bcc_ptr, bytes_remaining, ses,
				      sess_data->nls_cp);
	} else {
		decode_ascii_ssetup(&bcc_ptr, bytes_remaining, ses,
				    sess_data->nls_cp);
	}

out_free_ntlmsspblob:
	kfree(ntlmsspblob);
out:
	sess_free_buffer(sess_data);

	 if (!rc)
		rc = sess_establish_session(sess_data);

	/* Cleanup */
	kfree(ses->auth_key.response);
	ses->auth_key.response = NULL;
	kfree(ses->ntlmssp);
	ses->ntlmssp = NULL;

	sess_data->func = NULL;
	sess_data->result = rc;
}