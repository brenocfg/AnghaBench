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
struct smb_rqst {int rq_nvec; int rq_npages; int rq_pagesz; int rq_offset; scalar_t__ rq_tailsz; struct kvec* rq_iov; } ;
struct kvec {int iov_len; } ;
struct TCP_Server_Info {TYPE_1__* vals; } ;
struct TYPE_2__ {scalar_t__ header_preamble_size; } ;

/* Variables and functions */

unsigned long
smb_rqst_len(struct TCP_Server_Info *server, struct smb_rqst *rqst)
{
	unsigned int i;
	struct kvec *iov;
	int nvec;
	unsigned long buflen = 0;

	if (server->vals->header_preamble_size == 0 &&
	    rqst->rq_nvec >= 2 && rqst->rq_iov[0].iov_len == 4) {
		iov = &rqst->rq_iov[1];
		nvec = rqst->rq_nvec - 1;
	} else {
		iov = rqst->rq_iov;
		nvec = rqst->rq_nvec;
	}

	/* total up iov array first */
	for (i = 0; i < nvec; i++)
		buflen += iov[i].iov_len;

	/*
	 * Add in the page array if there is one. The caller needs to make
	 * sure rq_offset and rq_tailsz are set correctly. If a buffer of
	 * multiple pages ends at page boundary, rq_tailsz needs to be set to
	 * PAGE_SIZE.
	 */
	if (rqst->rq_npages) {
		if (rqst->rq_npages == 1)
			buflen += rqst->rq_tailsz;
		else {
			/*
			 * If there is more than one page, calculate the
			 * buffer length based on rq_offset and rq_tailsz
			 */
			buflen += rqst->rq_pagesz * (rqst->rq_npages - 1) -
					rqst->rq_offset;
			buflen += rqst->rq_tailsz;
		}
	}

	return buflen;
}