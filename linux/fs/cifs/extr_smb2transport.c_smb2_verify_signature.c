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
struct smb_rqst {TYPE_1__* rq_iov; } ;
struct smb2_sync_hdr {scalar_t__ Command; char* Signature; } ;
struct TCP_Server_Info {int /*<<< orphan*/  srv_mutex; TYPE_2__* ops; int /*<<< orphan*/  session_estab; scalar_t__ ignore_signature; } ;
struct TYPE_4__ {unsigned int (* calc_signature ) (struct smb_rqst*,struct TCP_Server_Info*) ;} ;
struct TYPE_3__ {scalar_t__ iov_base; } ;

/* Variables and functions */
 int EACCES ; 
 int /*<<< orphan*/  FYI ; 
 scalar_t__ SMB2_NEGOTIATE ; 
 scalar_t__ SMB2_OPLOCK_BREAK ; 
 scalar_t__ SMB2_SESSION_SETUP ; 
 int SMB2_SIGNATURE_SIZE ; 
 int /*<<< orphan*/  cifs_dbg (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 scalar_t__ memcmp (char*,char*,int) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 unsigned int stub1 (struct smb_rqst*,struct TCP_Server_Info*) ; 

int
smb2_verify_signature(struct smb_rqst *rqst, struct TCP_Server_Info *server)
{
	unsigned int rc;
	char server_response_sig[16];
	struct smb2_sync_hdr *shdr =
			(struct smb2_sync_hdr *)rqst->rq_iov[0].iov_base;

	if ((shdr->Command == SMB2_NEGOTIATE) ||
	    (shdr->Command == SMB2_SESSION_SETUP) ||
	    (shdr->Command == SMB2_OPLOCK_BREAK) ||
	    server->ignore_signature ||
	    (!server->session_estab))
		return 0;

	/*
	 * BB what if signatures are supposed to be on for session but
	 * server does not send one? BB
	 */

	/* Do not need to verify session setups with signature "BSRSPYL " */
	if (memcmp(shdr->Signature, "BSRSPYL ", 8) == 0)
		cifs_dbg(FYI, "dummy signature received for smb command 0x%x\n",
			 shdr->Command);

	/*
	 * Save off the origiginal signature so we can modify the smb and check
	 * our calculated signature against what the server sent.
	 */
	memcpy(server_response_sig, shdr->Signature, SMB2_SIGNATURE_SIZE);

	memset(shdr->Signature, 0, SMB2_SIGNATURE_SIZE);

	mutex_lock(&server->srv_mutex);
	rc = server->ops->calc_signature(rqst, server);
	mutex_unlock(&server->srv_mutex);

	if (rc)
		return rc;

	if (memcmp(server_response_sig, shdr->Signature, SMB2_SIGNATURE_SIZE))
		return -EACCES;
	else
		return 0;
}