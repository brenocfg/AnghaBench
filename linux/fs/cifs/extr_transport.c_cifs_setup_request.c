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
struct smb_hdr {int dummy; } ;
struct mid_q_entry {int /*<<< orphan*/  sequence_number; } ;
struct cifs_ses {int /*<<< orphan*/  server; } ;
struct TYPE_2__ {scalar_t__ iov_base; int iov_len; } ;

/* Variables and functions */
 int EIO ; 
 struct mid_q_entry* ERR_PTR (int) ; 
 int allocate_mid (struct cifs_ses*,struct smb_hdr*,struct mid_q_entry**) ; 
 int /*<<< orphan*/  cifs_delete_mid (struct mid_q_entry*) ; 
 int cifs_sign_rqst (struct smb_rqst*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

struct mid_q_entry *
cifs_setup_request(struct cifs_ses *ses, struct smb_rqst *rqst)
{
	int rc;
	struct smb_hdr *hdr = (struct smb_hdr *)rqst->rq_iov[0].iov_base;
	struct mid_q_entry *mid;

	if (rqst->rq_iov[0].iov_len != 4 ||
	    rqst->rq_iov[0].iov_base + 4 != rqst->rq_iov[1].iov_base)
		return ERR_PTR(-EIO);

	rc = allocate_mid(ses, hdr, &mid);
	if (rc)
		return ERR_PTR(rc);
	rc = cifs_sign_rqst(rqst, ses->server, &mid->sequence_number);
	if (rc) {
		cifs_delete_mid(mid);
		return ERR_PTR(rc);
	}
	return mid;
}