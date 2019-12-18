#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct smb_rqst {int rq_nvec; struct kvec* rq_iov; } ;
struct kvec {int iov_base; int iov_len; } ;
struct cifs_ses {int dummy; } ;

/* Variables and functions */
 int CIFS_MAX_IOV_SIZE ; 
 int CIFS_NO_BUFFER ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int cifs_send_recv (unsigned int const,struct cifs_ses*,struct smb_rqst*,int*,int const,struct kvec*) ; 
 int /*<<< orphan*/  kfree (struct kvec*) ; 
 struct kvec* kmalloc_array (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct kvec*,struct kvec*,int) ; 
 int /*<<< orphan*/  memset (struct smb_rqst*,int /*<<< orphan*/ ,int) ; 

int
SendReceive2(const unsigned int xid, struct cifs_ses *ses,
	     struct kvec *iov, int n_vec, int *resp_buf_type /* ret */,
	     const int flags, struct kvec *resp_iov)
{
	struct smb_rqst rqst;
	struct kvec s_iov[CIFS_MAX_IOV_SIZE], *new_iov;
	int rc;

	if (n_vec + 1 > CIFS_MAX_IOV_SIZE) {
		new_iov = kmalloc_array(n_vec + 1, sizeof(struct kvec),
					GFP_KERNEL);
		if (!new_iov) {
			/* otherwise cifs_send_recv below sets resp_buf_type */
			*resp_buf_type = CIFS_NO_BUFFER;
			return -ENOMEM;
		}
	} else
		new_iov = s_iov;

	/* 1st iov is a RFC1001 length followed by the rest of the packet */
	memcpy(new_iov + 1, iov, (sizeof(struct kvec) * n_vec));

	new_iov[0].iov_base = new_iov[1].iov_base;
	new_iov[0].iov_len = 4;
	new_iov[1].iov_base += 4;
	new_iov[1].iov_len -= 4;

	memset(&rqst, 0, sizeof(struct smb_rqst));
	rqst.rq_iov = new_iov;
	rqst.rq_nvec = n_vec + 1;

	rc = cifs_send_recv(xid, ses, &rqst, resp_buf_type, flags, resp_iov);
	if (n_vec + 1 > CIFS_MAX_IOV_SIZE)
		kfree(new_iov);
	return rc;
}