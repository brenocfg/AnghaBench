#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct smb_hdr {int WordCount; int Uid; int Flags2; } ;
struct sess_data {int result; int /*<<< orphan*/ * func; int /*<<< orphan*/  nls_cp; TYPE_2__* iov; struct cifs_ses* ses; } ;
struct TYPE_10__ {int /*<<< orphan*/ * response; } ;
struct cifs_ses {int capabilities; int Suid; TYPE_4__ auth_key; int /*<<< orphan*/ * user_name; } ;
typedef  int /*<<< orphan*/  __u32 ;
typedef  scalar_t__ __u16 ;
struct TYPE_9__ {int /*<<< orphan*/  Action; } ;
struct TYPE_7__ {void* CaseSensitivePasswordLength; void* CaseInsensitivePasswordLength; int /*<<< orphan*/  Capabilities; } ;
struct TYPE_11__ {TYPE_3__ resp; TYPE_1__ req_no_secext; } ;
struct TYPE_8__ {char* iov_base; int iov_len; } ;
typedef  TYPE_5__ SESSION_SETUP_ANDX ;

/* Variables and functions */
 int CAP_UNICODE ; 
 int /*<<< orphan*/  CIFS_AUTH_RESP_SIZE ; 
 int CIFS_SESS_KEY_SIZE ; 
 int EIO ; 
 int /*<<< orphan*/  FYI ; 
 int GUEST_LOGIN ; 
 int SMBFLG2_UNICODE ; 
 int /*<<< orphan*/  VFS ; 
 int /*<<< orphan*/  ascii_ssetup_strings (char**,struct cifs_ses*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cifs_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  cifs_ssetup_hdr (struct cifs_ses*,TYPE_5__*) ; 
 void* cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  decode_ascii_ssetup (char**,scalar_t__,struct cifs_ses*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  decode_unicode_ssetup (char**,scalar_t__,struct cifs_ses*,int /*<<< orphan*/ ) ; 
 scalar_t__ get_bcc (struct smb_hdr*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* pByteArea (struct smb_hdr*) ; 
 int sess_alloc_buffer (struct sess_data*,int) ; 
 int sess_establish_session (struct sess_data*) ; 
 int /*<<< orphan*/  sess_free_buffer (struct sess_data*) ; 
 int sess_sendreceive (struct sess_data*) ; 
 int setup_ntlm_response (struct cifs_ses*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unicode_ssetup_strings (char**,struct cifs_ses*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
sess_auth_ntlm(struct sess_data *sess_data)
{
	int rc = 0;
	struct smb_hdr *smb_buf;
	SESSION_SETUP_ANDX *pSMB;
	char *bcc_ptr;
	struct cifs_ses *ses = sess_data->ses;
	__u32 capabilities;
	__u16 bytes_remaining;

	/* old style NTLM sessionsetup */
	/* wct = 13 */
	rc = sess_alloc_buffer(sess_data, 13);
	if (rc)
		goto out;

	pSMB = (SESSION_SETUP_ANDX *)sess_data->iov[0].iov_base;
	bcc_ptr = sess_data->iov[2].iov_base;
	capabilities = cifs_ssetup_hdr(ses, pSMB);

	pSMB->req_no_secext.Capabilities = cpu_to_le32(capabilities);
	if (ses->user_name != NULL) {
		pSMB->req_no_secext.CaseInsensitivePasswordLength =
				cpu_to_le16(CIFS_AUTH_RESP_SIZE);
		pSMB->req_no_secext.CaseSensitivePasswordLength =
				cpu_to_le16(CIFS_AUTH_RESP_SIZE);

		/* calculate ntlm response and session key */
		rc = setup_ntlm_response(ses, sess_data->nls_cp);
		if (rc) {
			cifs_dbg(VFS, "Error %d during NTLM authentication\n",
					 rc);
			goto out;
		}

		/* copy ntlm response */
		memcpy(bcc_ptr, ses->auth_key.response + CIFS_SESS_KEY_SIZE,
				CIFS_AUTH_RESP_SIZE);
		bcc_ptr += CIFS_AUTH_RESP_SIZE;
		memcpy(bcc_ptr, ses->auth_key.response + CIFS_SESS_KEY_SIZE,
				CIFS_AUTH_RESP_SIZE);
		bcc_ptr += CIFS_AUTH_RESP_SIZE;
	} else {
		pSMB->req_no_secext.CaseInsensitivePasswordLength = 0;
		pSMB->req_no_secext.CaseSensitivePasswordLength = 0;
	}

	if (ses->capabilities & CAP_UNICODE) {
		/* unicode strings must be word aligned */
		if (sess_data->iov[0].iov_len % 2) {
			*bcc_ptr = 0;
			bcc_ptr++;
		}
		unicode_ssetup_strings(&bcc_ptr, ses, sess_data->nls_cp);
	} else {
		ascii_ssetup_strings(&bcc_ptr, ses, sess_data->nls_cp);
	}


	sess_data->iov[2].iov_len = (long) bcc_ptr -
			(long) sess_data->iov[2].iov_base;

	rc = sess_sendreceive(sess_data);
	if (rc)
		goto out;

	pSMB = (SESSION_SETUP_ANDX *)sess_data->iov[0].iov_base;
	smb_buf = (struct smb_hdr *)sess_data->iov[0].iov_base;

	if (smb_buf->WordCount != 3) {
		rc = -EIO;
		cifs_dbg(VFS, "bad word count %d\n", smb_buf->WordCount);
		goto out;
	}

	if (le16_to_cpu(pSMB->resp.Action) & GUEST_LOGIN)
		cifs_dbg(FYI, "Guest login\n"); /* BB mark SesInfo struct? */

	ses->Suid = smb_buf->Uid;   /* UID left in wire format (le) */
	cifs_dbg(FYI, "UID = %llu\n", ses->Suid);

	bytes_remaining = get_bcc(smb_buf);
	bcc_ptr = pByteArea(smb_buf);

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

	rc = sess_establish_session(sess_data);
out:
	sess_data->result = rc;
	sess_data->func = NULL;
	sess_free_buffer(sess_data);
	kfree(ses->auth_key.response);
	ses->auth_key.response = NULL;
}