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
struct kvec {int dummy; } ;
struct TCP_Server_Info {int dummy; } ;
typedef  int /*<<< orphan*/  __u32 ;

/* Variables and functions */
 int cifs_sign_rqst (struct smb_rqst*,struct TCP_Server_Info*,int /*<<< orphan*/ *) ; 

int cifs_sign_smbv(struct kvec *iov, int n_vec, struct TCP_Server_Info *server,
		   __u32 *pexpected_response_sequence)
{
	struct smb_rqst rqst = { .rq_iov = iov,
				 .rq_nvec = n_vec };

	return cifs_sign_rqst(&rqst, server, pexpected_response_sequence);
}