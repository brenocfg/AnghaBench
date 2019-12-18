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
struct tcon_link {int dummy; } ;
struct inode {int /*<<< orphan*/  i_sb; } ;
struct cifs_tcon {int dummy; } ;
struct cifs_sb_info {int dummy; } ;
struct cifs_open_parms {int desired_access; int create_options; char const* path; int reconnect; struct cifs_fid* fid; int /*<<< orphan*/  disposition; struct cifs_sb_info* cifs_sb; struct cifs_tcon* tcon; } ;
struct cifs_ntsd {int dummy; } ;
struct cifs_fid {int /*<<< orphan*/  netfid; } ;
typedef  int /*<<< orphan*/  __u32 ;

/* Variables and functions */
 int /*<<< orphan*/  CIFSSMBClose (unsigned int,struct cifs_tcon*,int /*<<< orphan*/ ) ; 
 int CIFSSMBSetCIFSACL (unsigned int,struct cifs_tcon*,int /*<<< orphan*/ ,struct cifs_ntsd*,int /*<<< orphan*/ ,int) ; 
 int CIFS_ACL_GROUP ; 
 int CIFS_ACL_OWNER ; 
 struct cifs_sb_info* CIFS_SB (int /*<<< orphan*/ ) ; 
 int CIFS_open (unsigned int,struct cifs_open_parms*,int*,int /*<<< orphan*/ *) ; 
 int CREATE_OPEN_BACKUP_INTENT ; 
 int /*<<< orphan*/  FILE_OPEN ; 
 scalar_t__ IS_ERR (struct tcon_link*) ; 
 int /*<<< orphan*/  NOISY ; 
 int PTR_ERR (struct tcon_link*) ; 
 int /*<<< orphan*/  VFS ; 
 int WRITE_DAC ; 
 int WRITE_OWNER ; 
 scalar_t__ backup_cred (struct cifs_sb_info*) ; 
 int /*<<< orphan*/  cifs_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  cifs_put_tlink (struct tcon_link*) ; 
 struct tcon_link* cifs_sb_tlink (struct cifs_sb_info*) ; 
 int /*<<< orphan*/  free_xid (unsigned int) ; 
 unsigned int get_xid () ; 
 struct cifs_tcon* tlink_tcon (struct tcon_link*) ; 

int set_cifs_acl(struct cifs_ntsd *pnntsd, __u32 acllen,
			struct inode *inode, const char *path, int aclflag)
{
	int oplock = 0;
	unsigned int xid;
	int rc, access_flags, create_options = 0;
	struct cifs_tcon *tcon;
	struct cifs_sb_info *cifs_sb = CIFS_SB(inode->i_sb);
	struct tcon_link *tlink = cifs_sb_tlink(cifs_sb);
	struct cifs_fid fid;
	struct cifs_open_parms oparms;

	if (IS_ERR(tlink))
		return PTR_ERR(tlink);

	tcon = tlink_tcon(tlink);
	xid = get_xid();

	if (backup_cred(cifs_sb))
		create_options |= CREATE_OPEN_BACKUP_INTENT;

	if (aclflag == CIFS_ACL_OWNER || aclflag == CIFS_ACL_GROUP)
		access_flags = WRITE_OWNER;
	else
		access_flags = WRITE_DAC;

	oparms.tcon = tcon;
	oparms.cifs_sb = cifs_sb;
	oparms.desired_access = access_flags;
	oparms.create_options = create_options;
	oparms.disposition = FILE_OPEN;
	oparms.path = path;
	oparms.fid = &fid;
	oparms.reconnect = false;

	rc = CIFS_open(xid, &oparms, &oplock, NULL);
	if (rc) {
		cifs_dbg(VFS, "Unable to open file to set ACL\n");
		goto out;
	}

	rc = CIFSSMBSetCIFSACL(xid, tcon, fid.netfid, pnntsd, acllen, aclflag);
	cifs_dbg(NOISY, "SetCIFSACL rc = %d\n", rc);

	CIFSSMBClose(xid, tcon, fid.netfid);
out:
	free_xid(xid);
	cifs_put_tlink(tlink);
	return rc;
}