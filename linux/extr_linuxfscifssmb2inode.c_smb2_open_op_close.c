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
struct smb2_file_all_info {int dummy; } ;
struct cifs_tcon {int nohandlecache; int /*<<< orphan*/  crfid; } ;
struct cifs_sb_info {int dummy; } ;
struct cifs_open_parms {int reconnect; struct cifs_fid* fid; scalar_t__ create_options; scalar_t__ disposition; scalar_t__ desired_access; struct cifs_tcon* tcon; } ;
struct cifs_fid {int /*<<< orphan*/  volatile_fid; int /*<<< orphan*/  persistent_fid; } ;
typedef  int /*<<< orphan*/  __u8 ;
typedef  scalar_t__ __u32 ;
typedef  int /*<<< orphan*/  __le64 ;
typedef  int /*<<< orphan*/  __le16 ;
struct TYPE_2__ {int /*<<< orphan*/  tgid; } ;
typedef  int /*<<< orphan*/  FILE_BASIC_INFO ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ FILE_OPEN ; 
 scalar_t__ FILE_READ_ATTRIBUTES ; 
 int /*<<< orphan*/  SMB2_OPLOCK_LEVEL_NONE ; 
#define  SMB2_OP_DELETE 135 
#define  SMB2_OP_HARDLINK 134 
#define  SMB2_OP_MKDIR 133 
#define  SMB2_OP_QUERY_INFO 132 
#define  SMB2_OP_RENAME 131 
#define  SMB2_OP_RMDIR 130 
#define  SMB2_OP_SET_EOF 129 
#define  SMB2_OP_SET_INFO 128 
 int SMB2_close (unsigned int const,struct cifs_tcon*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int SMB2_open (unsigned int const,struct cifs_open_parms*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int SMB2_query_info (unsigned int const,struct cifs_tcon*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct smb2_file_all_info*) ; 
 int SMB2_rename (unsigned int const,struct cifs_tcon*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int SMB2_rmdir (unsigned int const,struct cifs_tcon*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int SMB2_set_eof (unsigned int const,struct cifs_tcon*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int SMB2_set_hardlink (unsigned int const,struct cifs_tcon*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int SMB2_set_info (unsigned int const,struct cifs_tcon*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VFS ; 
 int /*<<< orphan*/ * cifs_convert_path_to_utf16 (char const*,struct cifs_sb_info*) ; 
 int /*<<< orphan*/  cifs_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  close_shroot (int /*<<< orphan*/ *) ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int open_shroot (unsigned int const,struct cifs_tcon*,struct cifs_fid*) ; 
 scalar_t__ strcmp (char const*,char*) ; 

__attribute__((used)) static int
smb2_open_op_close(const unsigned int xid, struct cifs_tcon *tcon,
		   struct cifs_sb_info *cifs_sb, const char *full_path,
		   __u32 desired_access, __u32 create_disposition,
		   __u32 create_options, void *data, int command)
{
	int rc, tmprc = 0;
	__le16 *utf16_path = NULL;
	__u8 oplock = SMB2_OPLOCK_LEVEL_NONE;
	struct cifs_open_parms oparms;
	struct cifs_fid fid;
	bool use_cached_root_handle = false;

	if ((strcmp(full_path, "") == 0) && (create_options == 0) &&
	    (desired_access == FILE_READ_ATTRIBUTES) &&
	    (create_disposition == FILE_OPEN) &&
	    (tcon->nohandlecache == false)) {
		rc = open_shroot(xid, tcon, &fid);
		if (rc == 0)
			use_cached_root_handle = true;
	}

	if (use_cached_root_handle == false) {
		utf16_path = cifs_convert_path_to_utf16(full_path, cifs_sb);
		if (!utf16_path)
			return -ENOMEM;

		oparms.tcon = tcon;
		oparms.desired_access = desired_access;
		oparms.disposition = create_disposition;
		oparms.create_options = create_options;
		oparms.fid = &fid;
		oparms.reconnect = false;

		rc = SMB2_open(xid, &oparms, utf16_path, &oplock, NULL, NULL,
			       NULL);
		if (rc) {
			kfree(utf16_path);
			return rc;
		}
	}

	switch (command) {
	case SMB2_OP_DELETE:
		break;
	case SMB2_OP_QUERY_INFO:
		tmprc = SMB2_query_info(xid, tcon, fid.persistent_fid,
					fid.volatile_fid,
					(struct smb2_file_all_info *)data);
		break;
	case SMB2_OP_MKDIR:
		/*
		 * Directories are created through parameters in the
		 * SMB2_open() call.
		 */
		break;
	case SMB2_OP_RMDIR:
		tmprc = SMB2_rmdir(xid, tcon, fid.persistent_fid,
				   fid.volatile_fid);
		break;
	case SMB2_OP_RENAME:
		tmprc = SMB2_rename(xid, tcon, fid.persistent_fid,
				    fid.volatile_fid, (__le16 *)data);
		break;
	case SMB2_OP_HARDLINK:
		tmprc = SMB2_set_hardlink(xid, tcon, fid.persistent_fid,
					  fid.volatile_fid, (__le16 *)data);
		break;
	case SMB2_OP_SET_EOF:
		tmprc = SMB2_set_eof(xid, tcon, fid.persistent_fid,
				     fid.volatile_fid, current->tgid,
				     (__le64 *)data, false);
		break;
	case SMB2_OP_SET_INFO:
		tmprc = SMB2_set_info(xid, tcon, fid.persistent_fid,
				      fid.volatile_fid,
				      (FILE_BASIC_INFO *)data);
		break;
	default:
		cifs_dbg(VFS, "Invalid command\n");
		break;
	}

	if (use_cached_root_handle)
		close_shroot(&tcon->crfid);
	else
		rc = SMB2_close(xid, tcon, fid.persistent_fid, fid.volatile_fid);
	if (tmprc)
		rc = tmprc;
	kfree(utf16_path);
	return rc;
}