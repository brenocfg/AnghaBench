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
struct smb_rqst {scalar_t__ rq_iov; } ;

/* Variables and functions */
 int /*<<< orphan*/  SMB2_close_free (struct smb_rqst*) ; 
 int /*<<< orphan*/  SMB2_set_info_free (struct smb_rqst*) ; 

__attribute__((used)) static void
free_set_inf_compound(struct smb_rqst *rqst)
{
	if (rqst[1].rq_iov)
		SMB2_set_info_free(&rqst[1]);
	if (rqst[2].rq_iov)
		SMB2_close_free(&rqst[2]);
}