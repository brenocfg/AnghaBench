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
struct smb_rqst {int rq_nvec; TYPE_1__* rq_iov; } ;
struct TYPE_2__ {scalar_t__ iov_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  cifs_small_buf_release (scalar_t__) ; 
 int /*<<< orphan*/  kfree (scalar_t__) ; 
 scalar_t__ smb2_padding ; 

void
SMB2_open_free(struct smb_rqst *rqst)
{
	int i;

	if (rqst && rqst->rq_iov) {
		cifs_small_buf_release(rqst->rq_iov[0].iov_base);
		for (i = 1; i < rqst->rq_nvec; i++)
			if (rqst->rq_iov[i].iov_base != smb2_padding)
				kfree(rqst->rq_iov[i].iov_base);
	}
}