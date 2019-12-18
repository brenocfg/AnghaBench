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
struct TYPE_2__ {struct smb2_file_all_info file_all_info; scalar_t__ file_all_info_is_valid; } ;
struct cifs_tcon {int nohandlecache; TYPE_1__ crfid; } ;
struct cifs_sb_info {int dummy; } ;
struct cifs_fid {int /*<<< orphan*/  volatile_fid; int /*<<< orphan*/  persistent_fid; } ;
struct cifsFileInfo {int dummy; } ;
typedef  int /*<<< orphan*/  __u32 ;
typedef  int /*<<< orphan*/  FILE_ALL_INFO ;

/* Variables and functions */
 int /*<<< orphan*/  ACL_NO_MODE ; 
 int /*<<< orphan*/  CREATE_OPEN_BACKUP_INTENT ; 
 int ENOMEM ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  FILE_OPEN ; 
 int /*<<< orphan*/  FILE_READ_ATTRIBUTES ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  OPEN_REPARSE_POINT ; 
 int PATH_MAX ; 
 int /*<<< orphan*/  SMB2_OP_QUERY_INFO ; 
 int SMB2_query_info (unsigned int const,struct cifs_tcon*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct smb2_file_all_info*) ; 
 scalar_t__ backup_cred (struct cifs_sb_info*) ; 
 int /*<<< orphan*/  cifs_get_readable_path (struct cifs_tcon*,char const*,struct cifsFileInfo**) ; 
 int /*<<< orphan*/  close_shroot (TYPE_1__*) ; 
 int /*<<< orphan*/  kfree (struct smb2_file_all_info*) ; 
 struct smb2_file_all_info* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  move_smb2_info_to_cifs (int /*<<< orphan*/ *,struct smb2_file_all_info*) ; 
 int open_shroot (unsigned int const,struct cifs_tcon*,struct cifs_fid*) ; 
 int smb2_compound_op (unsigned int const,struct cifs_tcon*,struct cifs_sb_info*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct smb2_file_all_info*,int /*<<< orphan*/ ,struct cifsFileInfo*) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

int
smb2_query_path_info(const unsigned int xid, struct cifs_tcon *tcon,
		     struct cifs_sb_info *cifs_sb, const char *full_path,
		     FILE_ALL_INFO *data, bool *adjust_tz, bool *symlink)
{
	int rc;
	struct smb2_file_all_info *smb2_data;
	__u32 create_options = 0;
	struct cifs_fid fid;
	bool no_cached_open = tcon->nohandlecache;
	struct cifsFileInfo *cfile;

	*adjust_tz = false;
	*symlink = false;

	smb2_data = kzalloc(sizeof(struct smb2_file_all_info) + PATH_MAX * 2,
			    GFP_KERNEL);
	if (smb2_data == NULL)
		return -ENOMEM;

	/* If it is a root and its handle is cached then use it */
	if (!strlen(full_path) && !no_cached_open) {
		rc = open_shroot(xid, tcon, &fid);
		if (rc)
			goto out;

		if (tcon->crfid.file_all_info_is_valid) {
			move_smb2_info_to_cifs(data,
					       &tcon->crfid.file_all_info);
		} else {
			rc = SMB2_query_info(xid, tcon, fid.persistent_fid,
					     fid.volatile_fid, smb2_data);
			if (!rc)
				move_smb2_info_to_cifs(data, smb2_data);
		}
		close_shroot(&tcon->crfid);
		goto out;
	}

	if (backup_cred(cifs_sb))
		create_options |= CREATE_OPEN_BACKUP_INTENT;

	cifs_get_readable_path(tcon, full_path, &cfile);
	rc = smb2_compound_op(xid, tcon, cifs_sb, full_path,
			      FILE_READ_ATTRIBUTES, FILE_OPEN, create_options,
			      ACL_NO_MODE, smb2_data, SMB2_OP_QUERY_INFO, cfile);
	if (rc == -EOPNOTSUPP) {
		*symlink = true;
		create_options |= OPEN_REPARSE_POINT;

		/* Failed on a symbolic link - query a reparse point info */
		rc = smb2_compound_op(xid, tcon, cifs_sb, full_path,
				      FILE_READ_ATTRIBUTES, FILE_OPEN,
				      create_options, ACL_NO_MODE,
				      smb2_data, SMB2_OP_QUERY_INFO, NULL);
	}
	if (rc)
		goto out;

	move_smb2_info_to_cifs(data, smb2_data);
out:
	kfree(smb2_data);
	return rc;
}