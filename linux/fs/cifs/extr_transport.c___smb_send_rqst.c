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
typedef  int /*<<< orphan*/  val ;
struct socket {int dummy; } ;
struct smb_rqst {int rq_nvec; unsigned int rq_npages; int /*<<< orphan*/ * rq_pages; struct kvec* rq_iov; } ;
struct msghdr {int /*<<< orphan*/  msg_iter; } ;
struct kvec {int iov_len; int /*<<< orphan*/ * iov_base; } ;
struct bio_vec {int /*<<< orphan*/  bv_len; int /*<<< orphan*/  bv_offset; int /*<<< orphan*/  bv_page; } ;
struct TCP_Server_Info {int /*<<< orphan*/  hostname; int /*<<< orphan*/  CurrentMid; int /*<<< orphan*/  tcpStatus; TYPE_1__* vals; scalar_t__ smbd_conn; struct socket* ssocket; } ;
typedef  int /*<<< orphan*/  sigset_t ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_2__ {scalar_t__ header_preamble_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  CifsNeedReconnect ; 
 int EAGAIN ; 
 int EINTR ; 
 int /*<<< orphan*/  FYI ; 
 int /*<<< orphan*/  SIG_BLOCK ; 
 int /*<<< orphan*/  SIG_SETMASK ; 
 int /*<<< orphan*/  SOL_TCP ; 
 int /*<<< orphan*/  TCP_CORK ; 
 int /*<<< orphan*/  VFS ; 
 int /*<<< orphan*/  WRITE ; 
 int /*<<< orphan*/  cifs_dbg (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ cifs_rdma_enabled (struct TCP_Server_Info*) ; 
 int /*<<< orphan*/  cifs_server_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  cpu_to_be32 (unsigned int) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  dump_smb (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  iov_iter_bvec (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct bio_vec*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iov_iter_kvec (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct kvec*,int,size_t) ; 
 int /*<<< orphan*/  kernel_setsockopt (struct socket*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  rqst_page_get_length (struct smb_rqst*,unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sigfillset (int /*<<< orphan*/ *) ; 
 scalar_t__ signal_pending (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sigprocmask (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ smb_rqst_len (struct TCP_Server_Info*,struct smb_rqst*) ; 
 int smb_send_kvec (struct TCP_Server_Info*,struct msghdr*,size_t*) ; 
 int smbd_send (struct TCP_Server_Info*,int,struct smb_rqst*) ; 
 int /*<<< orphan*/  trace_smb3_partial_send_reconnect (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
__smb_send_rqst(struct TCP_Server_Info *server, int num_rqst,
		struct smb_rqst *rqst)
{
	int rc = 0;
	struct kvec *iov;
	int n_vec;
	unsigned int send_length = 0;
	unsigned int i, j;
	sigset_t mask, oldmask;
	size_t total_len = 0, sent, size;
	struct socket *ssocket = server->ssocket;
	struct msghdr smb_msg;
	int val = 1;
	__be32 rfc1002_marker;

	if (cifs_rdma_enabled(server) && server->smbd_conn) {
		rc = smbd_send(server, num_rqst, rqst);
		goto smbd_done;
	}

	if (ssocket == NULL)
		return -EAGAIN;

	if (signal_pending(current)) {
		cifs_dbg(FYI, "signal is pending before sending any data\n");
		return -EINTR;
	}

	/* cork the socket */
	kernel_setsockopt(ssocket, SOL_TCP, TCP_CORK,
				(char *)&val, sizeof(val));

	for (j = 0; j < num_rqst; j++)
		send_length += smb_rqst_len(server, &rqst[j]);
	rfc1002_marker = cpu_to_be32(send_length);

	/*
	 * We should not allow signals to interrupt the network send because
	 * any partial send will cause session reconnects thus increasing
	 * latency of system calls and overload a server with unnecessary
	 * requests.
	 */

	sigfillset(&mask);
	sigprocmask(SIG_BLOCK, &mask, &oldmask);

	/* Generate a rfc1002 marker for SMB2+ */
	if (server->vals->header_preamble_size == 0) {
		struct kvec hiov = {
			.iov_base = &rfc1002_marker,
			.iov_len  = 4
		};
		iov_iter_kvec(&smb_msg.msg_iter, WRITE, &hiov, 1, 4);
		rc = smb_send_kvec(server, &smb_msg, &sent);
		if (rc < 0)
			goto unmask;

		total_len += sent;
		send_length += 4;
	}

	cifs_dbg(FYI, "Sending smb: smb_len=%u\n", send_length);

	for (j = 0; j < num_rqst; j++) {
		iov = rqst[j].rq_iov;
		n_vec = rqst[j].rq_nvec;

		size = 0;
		for (i = 0; i < n_vec; i++) {
			dump_smb(iov[i].iov_base, iov[i].iov_len);
			size += iov[i].iov_len;
		}

		iov_iter_kvec(&smb_msg.msg_iter, WRITE, iov, n_vec, size);

		rc = smb_send_kvec(server, &smb_msg, &sent);
		if (rc < 0)
			goto unmask;

		total_len += sent;

		/* now walk the page array and send each page in it */
		for (i = 0; i < rqst[j].rq_npages; i++) {
			struct bio_vec bvec;

			bvec.bv_page = rqst[j].rq_pages[i];
			rqst_page_get_length(&rqst[j], i, &bvec.bv_len,
					     &bvec.bv_offset);

			iov_iter_bvec(&smb_msg.msg_iter, WRITE,
				      &bvec, 1, bvec.bv_len);
			rc = smb_send_kvec(server, &smb_msg, &sent);
			if (rc < 0)
				break;

			total_len += sent;
		}
	}

unmask:
	sigprocmask(SIG_SETMASK, &oldmask, NULL);

	/*
	 * If signal is pending but we have already sent the whole packet to
	 * the server we need to return success status to allow a corresponding
	 * mid entry to be kept in the pending requests queue thus allowing
	 * to handle responses from the server by the client.
	 *
	 * If only part of the packet has been sent there is no need to hide
	 * interrupt because the session will be reconnected anyway, so there
	 * won't be any response from the server to handle.
	 */

	if (signal_pending(current) && (total_len != send_length)) {
		cifs_dbg(FYI, "signal is pending after attempt to send\n");
		rc = -EINTR;
	}

	/* uncork it */
	val = 0;
	kernel_setsockopt(ssocket, SOL_TCP, TCP_CORK,
				(char *)&val, sizeof(val));

	if ((total_len > 0) && (total_len != send_length)) {
		cifs_dbg(FYI, "partial send (wanted=%u sent=%zu): terminating session\n",
			 send_length, total_len);
		/*
		 * If we have only sent part of an SMB then the next SMB could
		 * be taken as the remainder of this one. We need to kill the
		 * socket so the server throws away the partial SMB
		 */
		server->tcpStatus = CifsNeedReconnect;
		trace_smb3_partial_send_reconnect(server->CurrentMid,
						  server->hostname);
	}
smbd_done:
	if (rc < 0 && rc != -EINTR)
		cifs_server_dbg(VFS, "Error %d sending data on socket to server\n",
			 rc);
	else if (rc > 0)
		rc = 0;

	return rc;
}