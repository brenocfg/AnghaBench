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
struct smb_rqst {TYPE_1__* rq_iov; } ;
struct smb_hdr {int /*<<< orphan*/  Flags2; } ;
struct mid_q_entry {int /*<<< orphan*/  sequence_number; } ;
struct TCP_Server_Info {scalar_t__ sign; } ;
struct TYPE_2__ {scalar_t__ iov_base; int iov_len; } ;

/* Variables and functions */
 struct mid_q_entry* AllocMidQEntry (struct smb_hdr*,struct TCP_Server_Info*) ; 
 int /*<<< orphan*/  DeleteMidQEntry (struct mid_q_entry*) ; 
 int EIO ; 
 int ENOMEM ; 
 struct mid_q_entry* ERR_PTR (int) ; 
 int /*<<< orphan*/  SMBFLG2_SECURITY_SIGNATURE ; 
 int cifs_sign_rqst (struct smb_rqst*,struct TCP_Server_Info*,int /*<<< orphan*/ *) ; 

struct mid_q_entry *
cifs_setup_async_request(struct TCP_Server_Info *server, struct smb_rqst *rqst)
{
	int rc;
	struct smb_hdr *hdr = (struct smb_hdr *)rqst->rq_iov[0].iov_base;
	struct mid_q_entry *mid;

	if (rqst->rq_iov[0].iov_len != 4 ||
	    rqst->rq_iov[0].iov_base + 4 != rqst->rq_iov[1].iov_base)
		return ERR_PTR(-EIO);

	/* enable signing if server requires it */
	if (server->sign)
		hdr->Flags2 |= SMBFLG2_SECURITY_SIGNATURE;

	mid = AllocMidQEntry(hdr, server);
	if (mid == NULL)
		return ERR_PTR(-ENOMEM);

	rc = cifs_sign_rqst(rqst, server, &mid->sequence_number);
	if (rc) {
		DeleteMidQEntry(mid);
		return ERR_PTR(rc);
	}

	return mid;
}