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
struct smb_vol {scalar_t__ posix_paths; scalar_t__ no_psx_acl; scalar_t__ no_linux_ext; } ;
struct TYPE_2__ {scalar_t__ Capability; } ;
struct cifs_tcon {int unix_ext; TYPE_1__ fsUnixInfo; } ;
struct cifs_sb_info {int /*<<< orphan*/  mnt_cifs_flags; } ;
typedef  int __u64 ;

/* Variables and functions */
 int /*<<< orphan*/  CIFSSMBQFSUnixInfo (unsigned int,struct cifs_tcon*) ; 
 scalar_t__ CIFSSMBSetFSUnixInfo (unsigned int,struct cifs_tcon*,int) ; 
 int /*<<< orphan*/  CIFS_MOUNT_POSIXACL ; 
 int /*<<< orphan*/  CIFS_MOUNT_POSIX_PATHS ; 
 int CIFS_UNIX_CAP_MASK ; 
 int CIFS_UNIX_EXTATTR_CAP ; 
 int CIFS_UNIX_FCNTL_CAP ; 
 int CIFS_UNIX_LARGE_READ_CAP ; 
 int CIFS_UNIX_LARGE_WRITE_CAP ; 
 int CIFS_UNIX_POSIX_ACL_CAP ; 
 int CIFS_UNIX_POSIX_PATHNAMES_CAP ; 
 int CIFS_UNIX_TRANSPORT_ENCRYPTION_CAP ; 
 int CIFS_UNIX_TRANSPORT_ENCRYPTION_MANDATORY_CAP ; 
 int CIFS_UNIX_XATTR_CAP ; 
 int /*<<< orphan*/  FYI ; 
 int /*<<< orphan*/  VFS ; 
 int /*<<< orphan*/  cifs_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int le64_to_cpu (scalar_t__) ; 

void reset_cifs_unix_caps(unsigned int xid, struct cifs_tcon *tcon,
			  struct cifs_sb_info *cifs_sb, struct smb_vol *vol_info)
{
	/* if we are reconnecting then should we check to see if
	 * any requested capabilities changed locally e.g. via
	 * remount but we can not do much about it here
	 * if they have (even if we could detect it by the following)
	 * Perhaps we could add a backpointer to array of sb from tcon
	 * or if we change to make all sb to same share the same
	 * sb as NFS - then we only have one backpointer to sb.
	 * What if we wanted to mount the server share twice once with
	 * and once without posixacls or posix paths? */
	__u64 saved_cap = le64_to_cpu(tcon->fsUnixInfo.Capability);

	if (vol_info && vol_info->no_linux_ext) {
		tcon->fsUnixInfo.Capability = 0;
		tcon->unix_ext = 0; /* Unix Extensions disabled */
		cifs_dbg(FYI, "Linux protocol extensions disabled\n");
		return;
	} else if (vol_info)
		tcon->unix_ext = 1; /* Unix Extensions supported */

	if (tcon->unix_ext == 0) {
		cifs_dbg(FYI, "Unix extensions disabled so not set on reconnect\n");
		return;
	}

	if (!CIFSSMBQFSUnixInfo(xid, tcon)) {
		__u64 cap = le64_to_cpu(tcon->fsUnixInfo.Capability);
		cifs_dbg(FYI, "unix caps which server supports %lld\n", cap);
		/* check for reconnect case in which we do not
		   want to change the mount behavior if we can avoid it */
		if (vol_info == NULL) {
			/* turn off POSIX ACL and PATHNAMES if not set
			   originally at mount time */
			if ((saved_cap & CIFS_UNIX_POSIX_ACL_CAP) == 0)
				cap &= ~CIFS_UNIX_POSIX_ACL_CAP;
			if ((saved_cap & CIFS_UNIX_POSIX_PATHNAMES_CAP) == 0) {
				if (cap & CIFS_UNIX_POSIX_PATHNAMES_CAP)
					cifs_dbg(VFS, "POSIXPATH support change\n");
				cap &= ~CIFS_UNIX_POSIX_PATHNAMES_CAP;
			} else if ((cap & CIFS_UNIX_POSIX_PATHNAMES_CAP) == 0) {
				cifs_dbg(VFS, "possible reconnect error\n");
				cifs_dbg(VFS, "server disabled POSIX path support\n");
			}
		}

		if (cap & CIFS_UNIX_TRANSPORT_ENCRYPTION_MANDATORY_CAP)
			cifs_dbg(VFS, "per-share encryption not supported yet\n");

		cap &= CIFS_UNIX_CAP_MASK;
		if (vol_info && vol_info->no_psx_acl)
			cap &= ~CIFS_UNIX_POSIX_ACL_CAP;
		else if (CIFS_UNIX_POSIX_ACL_CAP & cap) {
			cifs_dbg(FYI, "negotiated posix acl support\n");
			if (cifs_sb)
				cifs_sb->mnt_cifs_flags |=
					CIFS_MOUNT_POSIXACL;
		}

		if (vol_info && vol_info->posix_paths == 0)
			cap &= ~CIFS_UNIX_POSIX_PATHNAMES_CAP;
		else if (cap & CIFS_UNIX_POSIX_PATHNAMES_CAP) {
			cifs_dbg(FYI, "negotiate posix pathnames\n");
			if (cifs_sb)
				cifs_sb->mnt_cifs_flags |=
					CIFS_MOUNT_POSIX_PATHS;
		}

		cifs_dbg(FYI, "Negotiate caps 0x%x\n", (int)cap);
#ifdef CONFIG_CIFS_DEBUG2
		if (cap & CIFS_UNIX_FCNTL_CAP)
			cifs_dbg(FYI, "FCNTL cap\n");
		if (cap & CIFS_UNIX_EXTATTR_CAP)
			cifs_dbg(FYI, "EXTATTR cap\n");
		if (cap & CIFS_UNIX_POSIX_PATHNAMES_CAP)
			cifs_dbg(FYI, "POSIX path cap\n");
		if (cap & CIFS_UNIX_XATTR_CAP)
			cifs_dbg(FYI, "XATTR cap\n");
		if (cap & CIFS_UNIX_POSIX_ACL_CAP)
			cifs_dbg(FYI, "POSIX ACL cap\n");
		if (cap & CIFS_UNIX_LARGE_READ_CAP)
			cifs_dbg(FYI, "very large read cap\n");
		if (cap & CIFS_UNIX_LARGE_WRITE_CAP)
			cifs_dbg(FYI, "very large write cap\n");
		if (cap & CIFS_UNIX_TRANSPORT_ENCRYPTION_CAP)
			cifs_dbg(FYI, "transport encryption cap\n");
		if (cap & CIFS_UNIX_TRANSPORT_ENCRYPTION_MANDATORY_CAP)
			cifs_dbg(FYI, "mandatory transport encryption cap\n");
#endif /* CIFS_DEBUG2 */
		if (CIFSSMBSetFSUnixInfo(xid, tcon, cap)) {
			if (vol_info == NULL) {
				cifs_dbg(FYI, "resetting capabilities failed\n");
			} else
				cifs_dbg(VFS, "Negotiating Unix capabilities with the server failed. Consider mounting with the Unix Extensions disabled if problems are found by specifying the nounix mount option.\n");

		}
	}
}