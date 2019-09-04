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
struct smb_rqst {unsigned int rq_pagesz; unsigned int rq_offset; int rq_npages; unsigned int rq_tailsz; } ;

/* Variables and functions */

void rqst_page_get_length(struct smb_rqst *rqst, unsigned int page,
				unsigned int *len, unsigned int *offset)
{
	*len = rqst->rq_pagesz;
	*offset = (page == 0) ? rqst->rq_offset : 0;

	if (rqst->rq_npages == 1 || page == rqst->rq_npages-1)
		*len = rqst->rq_tailsz;
	else if (page == 0)
		*len = rqst->rq_pagesz - rqst->rq_offset;
}