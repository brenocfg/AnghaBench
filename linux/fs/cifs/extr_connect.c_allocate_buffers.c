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
struct TCP_Server_Info {char* bigbuf; char* smallbuf; scalar_t__ large_buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  HEADER_SIZE (struct TCP_Server_Info*) ; 
 int /*<<< orphan*/  VFS ; 
 scalar_t__ cifs_buf_get () ; 
 int /*<<< orphan*/  cifs_server_dbg (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ cifs_small_buf_get () ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static bool
allocate_buffers(struct TCP_Server_Info *server)
{
	if (!server->bigbuf) {
		server->bigbuf = (char *)cifs_buf_get();
		if (!server->bigbuf) {
			cifs_server_dbg(VFS, "No memory for large SMB response\n");
			msleep(3000);
			/* retry will check if exiting */
			return false;
		}
	} else if (server->large_buf) {
		/* we are reusing a dirty large buf, clear its start */
		memset(server->bigbuf, 0, HEADER_SIZE(server));
	}

	if (!server->smallbuf) {
		server->smallbuf = (char *)cifs_small_buf_get();
		if (!server->smallbuf) {
			cifs_server_dbg(VFS, "No memory for SMB response\n");
			msleep(1000);
			/* retry will check if exiting */
			return false;
		}
		/* beginning of smb buffer is cleared in our buf_get */
	} else {
		/* if existing small buf clear beginning */
		memset(server->smallbuf, 0, HEADER_SIZE(server));
	}

	return true;
}