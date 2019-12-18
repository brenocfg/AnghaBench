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
struct msghdr {scalar_t__ msg_controllen; int /*<<< orphan*/ * msg_control; } ;
struct TCP_Server_Info {scalar_t__ tcpStatus; int /*<<< orphan*/  ssocket; scalar_t__ smbd_conn; } ;

/* Variables and functions */
 scalar_t__ CifsExiting ; 
 scalar_t__ CifsNeedReconnect ; 
 int EAGAIN ; 
 int ECONNABORTED ; 
 int EINTR ; 
 int ERESTARTSYS ; 
 int ESHUTDOWN ; 
 int /*<<< orphan*/  FYI ; 
 int /*<<< orphan*/  cifs_dbg (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ cifs_rdma_enabled (struct TCP_Server_Info*) ; 
 int /*<<< orphan*/  cifs_reconnect (struct TCP_Server_Info*) ; 
 scalar_t__ msg_data_left (struct msghdr*) ; 
 scalar_t__ server_unresponsive (struct TCP_Server_Info*) ; 
 int smbd_recv (scalar_t__,struct msghdr*) ; 
 int sock_recvmsg (int /*<<< orphan*/ ,struct msghdr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  try_to_freeze () ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 
 scalar_t__ zero_credits (struct TCP_Server_Info*) ; 

__attribute__((used)) static int
cifs_readv_from_socket(struct TCP_Server_Info *server, struct msghdr *smb_msg)
{
	int length = 0;
	int total_read;

	smb_msg->msg_control = NULL;
	smb_msg->msg_controllen = 0;

	for (total_read = 0; msg_data_left(smb_msg); total_read += length) {
		try_to_freeze();

		/* reconnect if no credits and no requests in flight */
		if (zero_credits(server)) {
			cifs_reconnect(server);
			return -ECONNABORTED;
		}

		if (server_unresponsive(server))
			return -ECONNABORTED;
		if (cifs_rdma_enabled(server) && server->smbd_conn)
			length = smbd_recv(server->smbd_conn, smb_msg);
		else
			length = sock_recvmsg(server->ssocket, smb_msg, 0);

		if (server->tcpStatus == CifsExiting)
			return -ESHUTDOWN;

		if (server->tcpStatus == CifsNeedReconnect) {
			cifs_reconnect(server);
			return -ECONNABORTED;
		}

		if (length == -ERESTARTSYS ||
		    length == -EAGAIN ||
		    length == -EINTR) {
			/*
			 * Minimum sleep to prevent looping, allowing socket
			 * to clear and app threads to set tcpStatus
			 * CifsNeedReconnect if server hung.
			 */
			usleep_range(1000, 2000);
			length = 0;
			continue;
		}

		if (length <= 0) {
			cifs_dbg(FYI, "Received no data or error: %d\n", length);
			cifs_reconnect(server);
			return -ECONNABORTED;
		}
	}
	return total_read;
}