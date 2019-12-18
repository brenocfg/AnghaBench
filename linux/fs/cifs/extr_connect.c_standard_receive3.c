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
struct mid_q_entry {int dummy; } ;
struct TCP_Server_Info {char* smallbuf; unsigned int pdu_size; int large_buf; char* bigbuf; int total_read; TYPE_1__* vals; int /*<<< orphan*/  response_q; } ;
struct TYPE_2__ {unsigned int header_preamble_size; } ;

/* Variables and functions */
 unsigned int CIFSMaxBufSize ; 
 int ECONNABORTED ; 
 unsigned int HEADER_SIZE (struct TCP_Server_Info*) ; 
 int MAX_CIFS_SMALL_BUFFER_SIZE ; 
 unsigned int MAX_HEADER_SIZE (struct TCP_Server_Info*) ; 
 int /*<<< orphan*/  VFS ; 
 int cifs_handle_standard (struct TCP_Server_Info*,struct mid_q_entry*) ; 
 int cifs_read_from_socket (struct TCP_Server_Info*,char*,unsigned int) ; 
 int /*<<< orphan*/  cifs_reconnect (struct TCP_Server_Info*) ; 
 int /*<<< orphan*/  cifs_server_dbg (int /*<<< orphan*/ ,char*,unsigned int) ; 
 int /*<<< orphan*/  dump_smb (char*,int) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
standard_receive3(struct TCP_Server_Info *server, struct mid_q_entry *mid)
{
	int length;
	char *buf = server->smallbuf;
	unsigned int pdu_length = server->pdu_size;

	/* make sure this will fit in a large buffer */
	if (pdu_length > CIFSMaxBufSize + MAX_HEADER_SIZE(server) -
		server->vals->header_preamble_size) {
		cifs_server_dbg(VFS, "SMB response too long (%u bytes)\n", pdu_length);
		cifs_reconnect(server);
		wake_up(&server->response_q);
		return -ECONNABORTED;
	}

	/* switch to large buffer if too big for a small one */
	if (pdu_length > MAX_CIFS_SMALL_BUFFER_SIZE - 4) {
		server->large_buf = true;
		memcpy(server->bigbuf, buf, server->total_read);
		buf = server->bigbuf;
	}

	/* now read the rest */
	length = cifs_read_from_socket(server, buf + HEADER_SIZE(server) - 1,
				       pdu_length - HEADER_SIZE(server) + 1
				       + server->vals->header_preamble_size);

	if (length < 0)
		return length;
	server->total_read += length;

	dump_smb(buf, server->total_read);

	return cifs_handle_standard(server, mid);
}