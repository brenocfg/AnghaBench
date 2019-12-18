#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct TYPE_11__ {scalar_t__ CifsError; } ;
struct smb_hdr {int WordCount; int Uid; TYPE_3__ Status; } ;
struct sess_data {scalar_t__ buf0_type; int result; int /*<<< orphan*/ * func; TYPE_2__* iov; struct cifs_ses* ses; } ;
struct ntlmssp_auth {int dummy; } ;
struct TYPE_13__ {TYPE_7__* response; } ;
struct cifs_ses {int Suid; TYPE_7__* ntlmssp; TYPE_5__ auth_key; } ;
typedef  int __u16 ;
struct TYPE_15__ {int sesskey_per_smbsess; } ;
struct TYPE_12__ {int /*<<< orphan*/  SecurityBlobLength; } ;
struct TYPE_9__ {int /*<<< orphan*/  SecurityBlobLength; scalar_t__ SecurityBlob; } ;
struct TYPE_14__ {TYPE_4__ resp; TYPE_1__ req; } ;
struct TYPE_10__ {int iov_len; scalar_t__ iov_base; } ;
typedef  TYPE_6__ SESSION_SETUP_ANDX ;
typedef  int /*<<< orphan*/  NEGOTIATE_MESSAGE ;

/* Variables and functions */
 scalar_t__ CIFS_NO_BUFFER ; 
 int EINVAL ; 
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  FYI ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  NT_STATUS_MORE_PROCESSING_REQUIRED ; 
 int /*<<< orphan*/  VFS ; 
 int _sess_auth_rawntlmssp_assemble_req (struct sess_data*) ; 
 int /*<<< orphan*/  build_ntlmssp_negotiate_blob (scalar_t__,struct cifs_ses*) ; 
 int /*<<< orphan*/  cifs_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 scalar_t__ cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int decode_ntlmssp_challenge (char*,int,struct cifs_ses*) ; 
 int get_bcc (struct smb_hdr*) ; 
 int /*<<< orphan*/  kfree (TYPE_7__*) ; 
 TYPE_7__* kmalloc (int,int /*<<< orphan*/ ) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 char* pByteArea (struct smb_hdr*) ; 
 int sess_alloc_buffer (struct sess_data*,int) ; 
 int /*<<< orphan*/ * sess_auth_rawntlmssp_authenticate ; 
 int /*<<< orphan*/  sess_free_buffer (struct sess_data*) ; 
 int sess_sendreceive (struct sess_data*) ; 

__attribute__((used)) static void
sess_auth_rawntlmssp_negotiate(struct sess_data *sess_data)
{
	int rc;
	struct smb_hdr *smb_buf;
	SESSION_SETUP_ANDX *pSMB;
	struct cifs_ses *ses = sess_data->ses;
	__u16 bytes_remaining;
	char *bcc_ptr;
	u16 blob_len;

	cifs_dbg(FYI, "rawntlmssp session setup negotiate phase\n");

	/*
	 * if memory allocation is successful, caller of this function
	 * frees it.
	 */
	ses->ntlmssp = kmalloc(sizeof(struct ntlmssp_auth), GFP_KERNEL);
	if (!ses->ntlmssp) {
		rc = -ENOMEM;
		goto out;
	}
	ses->ntlmssp->sesskey_per_smbsess = false;

	/* wct = 12 */
	rc = sess_alloc_buffer(sess_data, 12);
	if (rc)
		goto out;

	pSMB = (SESSION_SETUP_ANDX *)sess_data->iov[0].iov_base;

	/* Build security blob before we assemble the request */
	build_ntlmssp_negotiate_blob(pSMB->req.SecurityBlob, ses);
	sess_data->iov[1].iov_len = sizeof(NEGOTIATE_MESSAGE);
	sess_data->iov[1].iov_base = pSMB->req.SecurityBlob;
	pSMB->req.SecurityBlobLength = cpu_to_le16(sizeof(NEGOTIATE_MESSAGE));

	rc = _sess_auth_rawntlmssp_assemble_req(sess_data);
	if (rc)
		goto out;

	rc = sess_sendreceive(sess_data);

	pSMB = (SESSION_SETUP_ANDX *)sess_data->iov[0].iov_base;
	smb_buf = (struct smb_hdr *)sess_data->iov[0].iov_base;

	/* If true, rc here is expected and not an error */
	if (sess_data->buf0_type != CIFS_NO_BUFFER &&
	    smb_buf->Status.CifsError ==
			cpu_to_le32(NT_STATUS_MORE_PROCESSING_REQUIRED))
		rc = 0;

	if (rc)
		goto out;

	cifs_dbg(FYI, "rawntlmssp session setup challenge phase\n");

	if (smb_buf->WordCount != 4) {
		rc = -EIO;
		cifs_dbg(VFS, "bad word count %d\n", smb_buf->WordCount);
		goto out;
	}

	ses->Suid = smb_buf->Uid;   /* UID left in wire format (le) */
	cifs_dbg(FYI, "UID = %llu\n", ses->Suid);

	bytes_remaining = get_bcc(smb_buf);
	bcc_ptr = pByteArea(smb_buf);

	blob_len = le16_to_cpu(pSMB->resp.SecurityBlobLength);
	if (blob_len > bytes_remaining) {
		cifs_dbg(VFS, "bad security blob length %d\n",
				blob_len);
		rc = -EINVAL;
		goto out;
	}

	rc = decode_ntlmssp_challenge(bcc_ptr, blob_len, ses);
out:
	sess_free_buffer(sess_data);

	if (!rc) {
		sess_data->func = sess_auth_rawntlmssp_authenticate;
		return;
	}

	/* Else error. Cleanup */
	kfree(ses->auth_key.response);
	ses->auth_key.response = NULL;
	kfree(ses->ntlmssp);
	ses->ntlmssp = NULL;

	sess_data->func = NULL;
	sess_data->result = rc;
}