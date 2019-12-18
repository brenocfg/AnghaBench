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
struct smb2_transform_hdr {int /*<<< orphan*/  OriginalMessageSize; } ;
struct smb2_sync_hdr {int dummy; } ;
struct mid_q_entry {int dummy; } ;
struct TCP_Server_Info {char* smallbuf; unsigned int pdu_size; int /*<<< orphan*/  response_q; } ;

/* Variables and functions */
 unsigned int CIFSMaxBufSize ; 
 int ECONNABORTED ; 
 unsigned int MAX_HEADER_SIZE (struct TCP_Server_Info*) ; 
 int /*<<< orphan*/  VFS ; 
 int /*<<< orphan*/  cifs_reconnect (struct TCP_Server_Info*) ; 
 int /*<<< orphan*/  cifs_server_dbg (int /*<<< orphan*/ ,char*,...) ; 
 unsigned int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int receive_encrypted_read (struct TCP_Server_Info*,struct mid_q_entry**,int*) ; 
 int receive_encrypted_standard (struct TCP_Server_Info*,struct mid_q_entry**,char**,int*) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
smb3_receive_transform(struct TCP_Server_Info *server,
		       struct mid_q_entry **mids, char **bufs, int *num_mids)
{
	char *buf = server->smallbuf;
	unsigned int pdu_length = server->pdu_size;
	struct smb2_transform_hdr *tr_hdr = (struct smb2_transform_hdr *)buf;
	unsigned int orig_len = le32_to_cpu(tr_hdr->OriginalMessageSize);

	if (pdu_length < sizeof(struct smb2_transform_hdr) +
						sizeof(struct smb2_sync_hdr)) {
		cifs_server_dbg(VFS, "Transform message is too small (%u)\n",
			 pdu_length);
		cifs_reconnect(server);
		wake_up(&server->response_q);
		return -ECONNABORTED;
	}

	if (pdu_length < orig_len + sizeof(struct smb2_transform_hdr)) {
		cifs_server_dbg(VFS, "Transform message is broken\n");
		cifs_reconnect(server);
		wake_up(&server->response_q);
		return -ECONNABORTED;
	}

	/* TODO: add support for compounds containing READ. */
	if (pdu_length > CIFSMaxBufSize + MAX_HEADER_SIZE(server)) {
		return receive_encrypted_read(server, &mids[0], num_mids);
	}

	return receive_encrypted_standard(server, mids, bufs, num_mids);
}