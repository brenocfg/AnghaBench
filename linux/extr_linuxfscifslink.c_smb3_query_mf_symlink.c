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
struct smb2_file_all_info {scalar_t__ EndOfFile; } ;
struct cifs_tcon {int dummy; } ;
struct cifs_sb_info {int dummy; } ;
struct cifs_open_parms {int reconnect; struct cifs_fid* fid; int /*<<< orphan*/  disposition; int /*<<< orphan*/  create_options; int /*<<< orphan*/  desired_access; struct cifs_sb_info* cifs_sb; struct cifs_tcon* tcon; } ;
struct cifs_io_parms {int /*<<< orphan*/  volatile_fid; int /*<<< orphan*/  persistent_fid; int /*<<< orphan*/  length; scalar_t__ offset; struct cifs_tcon* tcon; int /*<<< orphan*/  pid; int /*<<< orphan*/  netfid; } ;
struct cifs_fid {int /*<<< orphan*/  volatile_fid; int /*<<< orphan*/  persistent_fid; int /*<<< orphan*/  netfid; } ;
typedef  int /*<<< orphan*/  __u8 ;
typedef  struct smb2_file_all_info __le16 ;
struct TYPE_2__ {int /*<<< orphan*/  tgid; } ;

/* Variables and functions */
 int /*<<< orphan*/  CIFS_MF_SYMLINK_FILE_SIZE ; 
 int CIFS_NO_BUFFER ; 
 int /*<<< orphan*/  CREATE_NOT_DIR ; 
 int /*<<< orphan*/  CREATE_OPEN_BACKUP_INTENT ; 
 int ENOENT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  FILE_OPEN ; 
 int /*<<< orphan*/  GENERIC_READ ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int PATH_MAX ; 
 int /*<<< orphan*/  SMB2_OPLOCK_LEVEL_NONE ; 
 int /*<<< orphan*/  SMB2_close (unsigned int,struct cifs_tcon*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int SMB2_open (unsigned int,struct cifs_open_parms*,struct smb2_file_all_info*,int /*<<< orphan*/ *,struct smb2_file_all_info*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int SMB2_read (unsigned int,struct cifs_io_parms*,unsigned int*,char**,int*) ; 
 scalar_t__ backup_cred (struct cifs_sb_info*) ; 
 struct smb2_file_all_info* cifs_convert_path_to_utf16 (unsigned char const*,struct cifs_sb_info*) ; 
 scalar_t__ cpu_to_le64 (int /*<<< orphan*/ ) ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  kfree (struct smb2_file_all_info*) ; 
 struct smb2_file_all_info* kzalloc (int,int /*<<< orphan*/ ) ; 

int
smb3_query_mf_symlink(unsigned int xid, struct cifs_tcon *tcon,
		      struct cifs_sb_info *cifs_sb, const unsigned char *path,
		      char *pbuf, unsigned int *pbytes_read)
{
	int rc;
	struct cifs_fid fid;
	struct cifs_open_parms oparms;
	struct cifs_io_parms io_parms;
	int buf_type = CIFS_NO_BUFFER;
	__le16 *utf16_path;
	__u8 oplock = SMB2_OPLOCK_LEVEL_NONE;
	struct smb2_file_all_info *pfile_info = NULL;

	oparms.tcon = tcon;
	oparms.cifs_sb = cifs_sb;
	oparms.desired_access = GENERIC_READ;
	oparms.create_options = CREATE_NOT_DIR;
	if (backup_cred(cifs_sb))
		oparms.create_options |= CREATE_OPEN_BACKUP_INTENT;
	oparms.disposition = FILE_OPEN;
	oparms.fid = &fid;
	oparms.reconnect = false;

	utf16_path = cifs_convert_path_to_utf16(path, cifs_sb);
	if (utf16_path == NULL)
		return -ENOMEM;

	pfile_info = kzalloc(sizeof(struct smb2_file_all_info) + PATH_MAX * 2,
			     GFP_KERNEL);

	if (pfile_info == NULL) {
		kfree(utf16_path);
		return  -ENOMEM;
	}

	rc = SMB2_open(xid, &oparms, utf16_path, &oplock, pfile_info, NULL,
		       NULL);
	if (rc)
		goto qmf_out_open_fail;

	if (pfile_info->EndOfFile != cpu_to_le64(CIFS_MF_SYMLINK_FILE_SIZE)) {
		/* it's not a symlink */
		rc = -ENOENT; /* Is there a better rc to return? */
		goto qmf_out;
	}

	io_parms.netfid = fid.netfid;
	io_parms.pid = current->tgid;
	io_parms.tcon = tcon;
	io_parms.offset = 0;
	io_parms.length = CIFS_MF_SYMLINK_FILE_SIZE;
	io_parms.persistent_fid = fid.persistent_fid;
	io_parms.volatile_fid = fid.volatile_fid;
	rc = SMB2_read(xid, &io_parms, pbytes_read, &pbuf, &buf_type);
qmf_out:
	SMB2_close(xid, tcon, fid.persistent_fid, fid.volatile_fid);
qmf_out_open_fail:
	kfree(utf16_path);
	kfree(pfile_info);
	return rc;
}