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
struct TYPE_2__ {int /*<<< orphan*/  iov_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  cifs_small_buf_release (int /*<<< orphan*/ ) ; 

void
SMB2_query_info_free(struct smb_rqst *rqst)
{
	if (rqst && rqst->rq_iov)
		cifs_small_buf_release(rqst->rq_iov[0].iov_base); /* request */
}