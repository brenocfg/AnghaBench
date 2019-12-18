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
struct smb_rqst {int rq_nvec; unsigned int rq_npages; unsigned int rq_pagesz; unsigned int rq_tailsz; struct page** rq_pages; struct kvec* rq_iov; int /*<<< orphan*/ * member_0; } ;
struct smb2_transform_hdr {int dummy; } ;
struct page {int dummy; } ;
struct kvec {char* iov_base; int iov_len; } ;
struct TCP_Server_Info {unsigned int total_read; } ;

/* Variables and functions */
 int /*<<< orphan*/  FYI ; 
 unsigned int PAGE_SIZE ; 
 int /*<<< orphan*/  cifs_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int crypt_message (struct TCP_Server_Info*,int,struct smb_rqst*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memmove (char*,char*,unsigned int) ; 

__attribute__((used)) static int
decrypt_raw_data(struct TCP_Server_Info *server, char *buf,
		 unsigned int buf_data_size, struct page **pages,
		 unsigned int npages, unsigned int page_data_size)
{
	struct kvec iov[2];
	struct smb_rqst rqst = {NULL};
	int rc;

	iov[0].iov_base = buf;
	iov[0].iov_len = sizeof(struct smb2_transform_hdr);
	iov[1].iov_base = buf + sizeof(struct smb2_transform_hdr);
	iov[1].iov_len = buf_data_size;

	rqst.rq_iov = iov;
	rqst.rq_nvec = 2;
	rqst.rq_pages = pages;
	rqst.rq_npages = npages;
	rqst.rq_pagesz = PAGE_SIZE;
	rqst.rq_tailsz = (page_data_size % PAGE_SIZE) ? : PAGE_SIZE;

	rc = crypt_message(server, 1, &rqst, 0);
	cifs_dbg(FYI, "Decrypt message returned %d\n", rc);

	if (rc)
		return rc;

	memmove(buf, iov[1].iov_base, buf_data_size);

	server->total_read = buf_data_size + page_data_size;

	return rc;
}