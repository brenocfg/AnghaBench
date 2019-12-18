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
typedef  char smb_hdr ;
struct kvec {char* iov_base; int iov_len; } ;
struct TCP_Server_Info {int dummy; } ;

/* Variables and functions */
 int __smb_send_rqst (struct TCP_Server_Info*,int,struct smb_rqst*) ; 

int
smb_send(struct TCP_Server_Info *server, struct smb_hdr *smb_buffer,
	 unsigned int smb_buf_length)
{
	struct kvec iov[2];
	struct smb_rqst rqst = { .rq_iov = iov,
				 .rq_nvec = 2 };

	iov[0].iov_base = smb_buffer;
	iov[0].iov_len = 4;
	iov[1].iov_base = (char *)smb_buffer + 4;
	iov[1].iov_len = smb_buf_length;

	return __smb_send_rqst(server, 1, &rqst);
}