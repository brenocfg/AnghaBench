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
struct cifs_tcon {char* treeName; } ;
struct cifs_sb_info {int mnt_cifs_flags; int mnt_cifs_serverino_autodisabled; scalar_t__ master_tlink; } ;

/* Variables and functions */
 int CIFS_MOUNT_SERVER_INUM ; 
 int /*<<< orphan*/  VFS ; 
 int /*<<< orphan*/  cifs_dbg (int /*<<< orphan*/ ,char*,...) ; 
 struct cifs_tcon* cifs_sb_master_tcon (struct cifs_sb_info*) ; 

void
cifs_autodisable_serverino(struct cifs_sb_info *cifs_sb)
{
	if (cifs_sb->mnt_cifs_flags & CIFS_MOUNT_SERVER_INUM) {
		struct cifs_tcon *tcon = NULL;

		if (cifs_sb->master_tlink)
			tcon = cifs_sb_master_tcon(cifs_sb);

		cifs_sb->mnt_cifs_flags &= ~CIFS_MOUNT_SERVER_INUM;
		cifs_sb->mnt_cifs_serverino_autodisabled = true;
		cifs_dbg(VFS, "Autodisabling the use of server inode numbers on %s.\n",
			 tcon ? tcon->treeName : "new server");
		cifs_dbg(VFS, "The server doesn't seem to support them properly or the files might be on different servers (DFS).\n");
		cifs_dbg(VFS, "Hardlinks will not be recognized on this mount. Consider mounting with the \"noserverino\" option to silence this message.\n");

	}
}