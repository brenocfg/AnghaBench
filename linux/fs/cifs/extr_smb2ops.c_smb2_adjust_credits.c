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
struct cifs_credits {int value; scalar_t__ instance; } ;
struct TCP_Server_Info {scalar_t__ reconnect_instance; int /*<<< orphan*/  request_q; int /*<<< orphan*/  req_lock; int /*<<< orphan*/  credits; } ;

/* Variables and functions */
 int DIV_ROUND_UP (unsigned int const,int /*<<< orphan*/ ) ; 
 int EAGAIN ; 
 int ENOTSUPP ; 
 int /*<<< orphan*/  SMB2_MAX_BUFFER_SIZE ; 
 int /*<<< orphan*/  VFS ; 
 int /*<<< orphan*/  WARN_ONCE (int,char*,int,int) ; 
 int /*<<< orphan*/  cifs_server_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
smb2_adjust_credits(struct TCP_Server_Info *server,
		    struct cifs_credits *credits,
		    const unsigned int payload_size)
{
	int new_val = DIV_ROUND_UP(payload_size, SMB2_MAX_BUFFER_SIZE);

	if (!credits->value || credits->value == new_val)
		return 0;

	if (credits->value < new_val) {
		WARN_ONCE(1, "request has less credits (%d) than required (%d)",
			  credits->value, new_val);
		return -ENOTSUPP;
	}

	spin_lock(&server->req_lock);

	if (server->reconnect_instance != credits->instance) {
		spin_unlock(&server->req_lock);
		cifs_server_dbg(VFS, "trying to return %d credits to old session\n",
			 credits->value - new_val);
		return -EAGAIN;
	}

	server->credits += credits->value - new_val;
	spin_unlock(&server->req_lock);
	wake_up(&server->request_q);
	credits->value = new_val;
	return 0;
}