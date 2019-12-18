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
struct kvec {char* iov_base; scalar_t__ iov_len; } ;
struct cifs_ses {int dummy; } ;

/* Variables and functions */
 int CIFS_NO_RSP_BUF ; 
 int /*<<< orphan*/  NOISY ; 
 int SendReceive2 (unsigned int const,struct cifs_ses*,struct kvec*,int,int*,int,struct kvec*) ; 
 int /*<<< orphan*/  cifs_dbg (int /*<<< orphan*/ ,char*,int,int) ; 
 scalar_t__ get_rfc1002_length (char*) ; 

int
SendReceiveNoRsp(const unsigned int xid, struct cifs_ses *ses,
		 char *in_buf, int flags)
{
	int rc;
	struct kvec iov[1];
	struct kvec rsp_iov;
	int resp_buf_type;

	iov[0].iov_base = in_buf;
	iov[0].iov_len = get_rfc1002_length(in_buf) + 4;
	flags |= CIFS_NO_RSP_BUF;
	rc = SendReceive2(xid, ses, iov, 1, &resp_buf_type, flags, &rsp_iov);
	cifs_dbg(NOISY, "SendRcvNoRsp flags %d rc %d\n", flags, rc);

	return rc;
}