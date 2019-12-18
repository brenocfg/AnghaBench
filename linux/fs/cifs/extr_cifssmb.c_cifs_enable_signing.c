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
struct TCP_Server_Info {int sec_mode; int sign; TYPE_1__* vals; } ;
struct TYPE_2__ {int signing_required; int signing_enabled; } ;

/* Variables and functions */
 int CIFSSEC_MAY_SIGN ; 
 int CIFSSEC_MUST_SIGN ; 
 int ENOTSUPP ; 
 int /*<<< orphan*/  VFS ; 
 int /*<<< orphan*/  cifs_dbg (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ cifs_rdma_enabled (struct TCP_Server_Info*) ; 
 int global_secflags ; 

int
cifs_enable_signing(struct TCP_Server_Info *server, bool mnt_sign_required)
{
	bool srv_sign_required = server->sec_mode & server->vals->signing_required;
	bool srv_sign_enabled = server->sec_mode & server->vals->signing_enabled;
	bool mnt_sign_enabled = global_secflags & CIFSSEC_MAY_SIGN;

	/*
	 * Is signing required by mnt options? If not then check
	 * global_secflags to see if it is there.
	 */
	if (!mnt_sign_required)
		mnt_sign_required = ((global_secflags & CIFSSEC_MUST_SIGN) ==
						CIFSSEC_MUST_SIGN);

	/*
	 * If signing is required then it's automatically enabled too,
	 * otherwise, check to see if the secflags allow it.
	 */
	mnt_sign_enabled = mnt_sign_required ? mnt_sign_required :
				(global_secflags & CIFSSEC_MAY_SIGN);

	/* If server requires signing, does client allow it? */
	if (srv_sign_required) {
		if (!mnt_sign_enabled) {
			cifs_dbg(VFS, "Server requires signing, but it's disabled in SecurityFlags!");
			return -ENOTSUPP;
		}
		server->sign = true;
	}

	/* If client requires signing, does server allow it? */
	if (mnt_sign_required) {
		if (!srv_sign_enabled) {
			cifs_dbg(VFS, "Server does not support signing!");
			return -ENOTSUPP;
		}
		server->sign = true;
	}

	if (cifs_rdma_enabled(server) && server->sign)
		cifs_dbg(VFS, "Signing is enabled, and RDMA read/write will be disabled");

	return 0;
}