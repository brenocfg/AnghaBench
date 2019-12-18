#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct cifs_tcon {TYPE_2__* ses; } ;
struct cifs_fid {int /*<<< orphan*/  volatile_fid; int /*<<< orphan*/  persistent_fid; } ;
struct cifsInodeInfo {int /*<<< orphan*/  lease_key; } ;
struct TYPE_4__ {TYPE_1__* server; } ;
struct TYPE_3__ {int capabilities; } ;

/* Variables and functions */
 scalar_t__ CIFS_CACHE_READ (struct cifsInodeInfo*) ; 
 int SMB2_GLOBAL_CAP_LEASING ; 
 int SMB2_lease_break (int /*<<< orphan*/ ,struct cifs_tcon*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int SMB2_oplock_break (int /*<<< orphan*/ ,struct cifs_tcon*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  smb2_get_lease_state (struct cifsInodeInfo*) ; 

__attribute__((used)) static int
smb2_oplock_response(struct cifs_tcon *tcon, struct cifs_fid *fid,
		     struct cifsInodeInfo *cinode)
{
	if (tcon->ses->server->capabilities & SMB2_GLOBAL_CAP_LEASING)
		return SMB2_lease_break(0, tcon, cinode->lease_key,
					smb2_get_lease_state(cinode));

	return SMB2_oplock_break(0, tcon, fid->persistent_fid,
				 fid->volatile_fid,
				 CIFS_CACHE_READ(cinode) ? 1 : 0);
}