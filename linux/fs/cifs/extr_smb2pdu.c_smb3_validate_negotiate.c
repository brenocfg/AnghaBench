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
typedef  int u32 ;
struct validate_negotiate_info_rsp {scalar_t__ SecurityMode; scalar_t__ Dialect; int /*<<< orphan*/  Capabilities; scalar_t__ DialectCount; scalar_t__* Dialects; int /*<<< orphan*/  Guid; } ;
struct validate_negotiate_info_req {scalar_t__ SecurityMode; scalar_t__ Dialect; int /*<<< orphan*/  Capabilities; scalar_t__ DialectCount; scalar_t__* Dialects; int /*<<< orphan*/  Guid; } ;
struct cifs_tcon {TYPE_1__* ses; } ;
struct TCP_Server_Info {int dialect; int sec_mode; int capabilities; TYPE_2__* vals; int /*<<< orphan*/  client_guid; } ;
struct TYPE_4__ {int protocol_id; int /*<<< orphan*/  version_string; int /*<<< orphan*/  req_capabilities; } ;
struct TYPE_3__ {int session_flags; scalar_t__ sign; int /*<<< orphan*/ * user_name; struct TCP_Server_Info* server; } ;

/* Variables and functions */
 int CIFSMaxBufSize ; 
 int CIFSSEC_MAY_SIGN ; 
 int EIO ; 
 int ENOMEM ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  FSCTL_VALIDATE_NEGOTIATE_INFO ; 
 int /*<<< orphan*/  FYI ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  NO_FILE_ID ; 
 int SMB21_PROT_ID ; 
 int /*<<< orphan*/  SMB2_CLIENT_GUID_SIZE ; 
 int SMB2_LARGE_FILES ; 
 int SMB2_NEGOTIATE_SIGNING_ENABLED ; 
 int SMB2_NEGOTIATE_SIGNING_REQUIRED ; 
 int SMB2_NT_FIND ; 
 int SMB2_SESSION_FLAG_IS_GUEST ; 
 int SMB2_SESSION_FLAG_IS_NULL ; 
 int SMB2_ioctl (unsigned int const,struct cifs_tcon*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,int,int,char**,int*) ; 
 int SMB302_PROT_ID ; 
 int SMB30_PROT_ID ; 
 int SMB311_PROT_ID ; 
 int /*<<< orphan*/  SMB3ANY_VERSION_STRING ; 
 int /*<<< orphan*/  SMBDEFAULT_VERSION_STRING ; 
 int /*<<< orphan*/  VFS ; 
 int /*<<< orphan*/  cifs_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  cifs_tcon_dbg (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ cpu_to_le16 (int) ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int global_secflags ; 
 int /*<<< orphan*/  kfree (struct validate_negotiate_info_rsp*) ; 
 struct validate_negotiate_info_rsp* kmalloc (int,int /*<<< orphan*/ ) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int smb3_validate_negotiate(const unsigned int xid, struct cifs_tcon *tcon)
{
	int rc;
	struct validate_negotiate_info_req *pneg_inbuf;
	struct validate_negotiate_info_rsp *pneg_rsp = NULL;
	u32 rsplen;
	u32 inbuflen; /* max of 4 dialects */
	struct TCP_Server_Info *server = tcon->ses->server;

	cifs_dbg(FYI, "validate negotiate\n");

	/* In SMB3.11 preauth integrity supersedes validate negotiate */
	if (server->dialect == SMB311_PROT_ID)
		return 0;

	/*
	 * validation ioctl must be signed, so no point sending this if we
	 * can not sign it (ie are not known user).  Even if signing is not
	 * required (enabled but not negotiated), in those cases we selectively
	 * sign just this, the first and only signed request on a connection.
	 * Having validation of negotiate info  helps reduce attack vectors.
	 */
	if (tcon->ses->session_flags & SMB2_SESSION_FLAG_IS_GUEST)
		return 0; /* validation requires signing */

	if (tcon->ses->user_name == NULL) {
		cifs_dbg(FYI, "Can't validate negotiate: null user mount\n");
		return 0; /* validation requires signing */
	}

	if (tcon->ses->session_flags & SMB2_SESSION_FLAG_IS_NULL)
		cifs_tcon_dbg(VFS, "Unexpected null user (anonymous) auth flag sent by server\n");

	pneg_inbuf = kmalloc(sizeof(*pneg_inbuf), GFP_NOFS);
	if (!pneg_inbuf)
		return -ENOMEM;

	pneg_inbuf->Capabilities =
			cpu_to_le32(server->vals->req_capabilities);
	memcpy(pneg_inbuf->Guid, server->client_guid,
					SMB2_CLIENT_GUID_SIZE);

	if (tcon->ses->sign)
		pneg_inbuf->SecurityMode =
			cpu_to_le16(SMB2_NEGOTIATE_SIGNING_REQUIRED);
	else if (global_secflags & CIFSSEC_MAY_SIGN)
		pneg_inbuf->SecurityMode =
			cpu_to_le16(SMB2_NEGOTIATE_SIGNING_ENABLED);
	else
		pneg_inbuf->SecurityMode = 0;


	if (strcmp(server->vals->version_string,
		SMB3ANY_VERSION_STRING) == 0) {
		pneg_inbuf->Dialects[0] = cpu_to_le16(SMB30_PROT_ID);
		pneg_inbuf->Dialects[1] = cpu_to_le16(SMB302_PROT_ID);
		pneg_inbuf->DialectCount = cpu_to_le16(2);
		/* structure is big enough for 3 dialects, sending only 2 */
		inbuflen = sizeof(*pneg_inbuf) -
				(2 * sizeof(pneg_inbuf->Dialects[0]));
	} else if (strcmp(server->vals->version_string,
		SMBDEFAULT_VERSION_STRING) == 0) {
		pneg_inbuf->Dialects[0] = cpu_to_le16(SMB21_PROT_ID);
		pneg_inbuf->Dialects[1] = cpu_to_le16(SMB30_PROT_ID);
		pneg_inbuf->Dialects[2] = cpu_to_le16(SMB302_PROT_ID);
		pneg_inbuf->Dialects[3] = cpu_to_le16(SMB311_PROT_ID);
		pneg_inbuf->DialectCount = cpu_to_le16(4);
		/* structure is big enough for 3 dialects */
		inbuflen = sizeof(*pneg_inbuf);
	} else {
		/* otherwise specific dialect was requested */
		pneg_inbuf->Dialects[0] =
			cpu_to_le16(server->vals->protocol_id);
		pneg_inbuf->DialectCount = cpu_to_le16(1);
		/* structure is big enough for 3 dialects, sending only 1 */
		inbuflen = sizeof(*pneg_inbuf) -
				sizeof(pneg_inbuf->Dialects[0]) * 2;
	}

	rc = SMB2_ioctl(xid, tcon, NO_FILE_ID, NO_FILE_ID,
		FSCTL_VALIDATE_NEGOTIATE_INFO, true /* is_fsctl */,
		(char *)pneg_inbuf, inbuflen, CIFSMaxBufSize,
		(char **)&pneg_rsp, &rsplen);
	if (rc == -EOPNOTSUPP) {
		/*
		 * Old Windows versions or Netapp SMB server can return
		 * not supported error. Client should accept it.
		 */
		cifs_tcon_dbg(VFS, "Server does not support validate negotiate\n");
		rc = 0;
		goto out_free_inbuf;
	} else if (rc != 0) {
		cifs_tcon_dbg(VFS, "validate protocol negotiate failed: %d\n", rc);
		rc = -EIO;
		goto out_free_inbuf;
	}

	rc = -EIO;
	if (rsplen != sizeof(*pneg_rsp)) {
		cifs_tcon_dbg(VFS, "invalid protocol negotiate response size: %d\n",
			 rsplen);

		/* relax check since Mac returns max bufsize allowed on ioctl */
		if (rsplen > CIFSMaxBufSize || rsplen < sizeof(*pneg_rsp))
			goto out_free_rsp;
	}

	/* check validate negotiate info response matches what we got earlier */
	if (pneg_rsp->Dialect != cpu_to_le16(server->dialect))
		goto vneg_out;

	if (pneg_rsp->SecurityMode != cpu_to_le16(server->sec_mode))
		goto vneg_out;

	/* do not validate server guid because not saved at negprot time yet */

	if ((le32_to_cpu(pneg_rsp->Capabilities) | SMB2_NT_FIND |
	      SMB2_LARGE_FILES) != server->capabilities)
		goto vneg_out;

	/* validate negotiate successful */
	rc = 0;
	cifs_dbg(FYI, "validate negotiate info successful\n");
	goto out_free_rsp;

vneg_out:
	cifs_tcon_dbg(VFS, "protocol revalidation - security settings mismatch\n");
out_free_rsp:
	kfree(pneg_rsp);
out_free_inbuf:
	kfree(pneg_inbuf);
	return rc;
}