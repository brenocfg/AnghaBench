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
struct smb_rqst {TYPE_1__* rq_iov; } ;
struct TYPE_5__ {scalar_t__ Reserved; int /*<<< orphan*/  SequenceNumber; } ;
struct TYPE_6__ {char* SecuritySignature; TYPE_2__ Sequence; } ;
struct smb_hdr {scalar_t__ Command; TYPE_3__ Signature; } ;
struct smb_com_lock_req {int LockType; } ;
struct TCP_Server_Info {int /*<<< orphan*/  srv_mutex; int /*<<< orphan*/  session_estab; } ;
typedef  int /*<<< orphan*/  __u32 ;
struct TYPE_4__ {scalar_t__ iov_base; int iov_len; } ;

/* Variables and functions */
 int EACCES ; 
 int EINVAL ; 
 int EIO ; 
 int /*<<< orphan*/  FYI ; 
 int LOCKING_ANDX_OPLOCK_RELEASE ; 
 scalar_t__ SMB_COM_LOCKING_ANDX ; 
 unsigned int cifs_calc_signature (struct smb_rqst*,struct TCP_Server_Info*,char*) ; 
 int /*<<< orphan*/  cifs_dbg (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 scalar_t__ memcmp (char*,char*,int) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int cifs_verify_signature(struct smb_rqst *rqst,
			  struct TCP_Server_Info *server,
			  __u32 expected_sequence_number)
{
	unsigned int rc;
	char server_response_sig[8];
	char what_we_think_sig_should_be[20];
	struct smb_hdr *cifs_pdu = (struct smb_hdr *)rqst->rq_iov[0].iov_base;

	if (rqst->rq_iov[0].iov_len != 4 ||
	    rqst->rq_iov[0].iov_base + 4 != rqst->rq_iov[1].iov_base)
		return -EIO;

	if (cifs_pdu == NULL || server == NULL)
		return -EINVAL;

	if (!server->session_estab)
		return 0;

	if (cifs_pdu->Command == SMB_COM_LOCKING_ANDX) {
		struct smb_com_lock_req *pSMB =
			(struct smb_com_lock_req *)cifs_pdu;
		if (pSMB->LockType & LOCKING_ANDX_OPLOCK_RELEASE)
			return 0;
	}

	/* BB what if signatures are supposed to be on for session but
	   server does not send one? BB */

	/* Do not need to verify session setups with signature "BSRSPYL "  */
	if (memcmp(cifs_pdu->Signature.SecuritySignature, "BSRSPYL ", 8) == 0)
		cifs_dbg(FYI, "dummy signature received for smb command 0x%x\n",
			 cifs_pdu->Command);

	/* save off the origiginal signature so we can modify the smb and check
		its signature against what the server sent */
	memcpy(server_response_sig, cifs_pdu->Signature.SecuritySignature, 8);

	cifs_pdu->Signature.Sequence.SequenceNumber =
					cpu_to_le32(expected_sequence_number);
	cifs_pdu->Signature.Sequence.Reserved = 0;

	mutex_lock(&server->srv_mutex);
	rc = cifs_calc_signature(rqst, server, what_we_think_sig_should_be);
	mutex_unlock(&server->srv_mutex);

	if (rc)
		return rc;

/*	cifs_dump_mem("what we think it should be: ",
		      what_we_think_sig_should_be, 16); */

	if (memcmp(server_response_sig, what_we_think_sig_should_be, 8))
		return -EACCES;
	else
		return 0;

}