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
struct smb2_file_all_info {int dummy; } ;
struct cifs_tcon {int dummy; } ;
struct cifs_sb_info {int dummy; } ;
typedef  int /*<<< orphan*/  FILE_ALL_INFO ;

/* Variables and functions */
 int ENOMEM ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  FILE_OPEN ; 
 int /*<<< orphan*/  FILE_READ_ATTRIBUTES ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  OPEN_REPARSE_POINT ; 
 int PATH_MAX ; 
 int /*<<< orphan*/  SMB2_OP_QUERY_INFO ; 
 int /*<<< orphan*/  kfree (struct smb2_file_all_info*) ; 
 struct smb2_file_all_info* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  move_smb2_info_to_cifs (int /*<<< orphan*/ *,struct smb2_file_all_info*) ; 
 int smb2_open_op_close (unsigned int const,struct cifs_tcon*,struct cifs_sb_info*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct smb2_file_all_info*,int /*<<< orphan*/ ) ; 

int
smb2_query_path_info(const unsigned int xid, struct cifs_tcon *tcon,
		     struct cifs_sb_info *cifs_sb, const char *full_path,
		     FILE_ALL_INFO *data, bool *adjust_tz, bool *symlink)
{
	int rc;
	struct smb2_file_all_info *smb2_data;

	*adjust_tz = false;
	*symlink = false;

	smb2_data = kzalloc(sizeof(struct smb2_file_all_info) + PATH_MAX * 2,
			    GFP_KERNEL);
	if (smb2_data == NULL)
		return -ENOMEM;

	rc = smb2_open_op_close(xid, tcon, cifs_sb, full_path,
				FILE_READ_ATTRIBUTES, FILE_OPEN, 0,
				smb2_data, SMB2_OP_QUERY_INFO);
	if (rc == -EOPNOTSUPP) {
		*symlink = true;
		/* Failed on a symbolic link - query a reparse point info */
		rc = smb2_open_op_close(xid, tcon, cifs_sb, full_path,
					FILE_READ_ATTRIBUTES, FILE_OPEN,
					OPEN_REPARSE_POINT, smb2_data,
					SMB2_OP_QUERY_INFO);
	}
	if (rc)
		goto out;

	move_smb2_info_to_cifs(data, smb2_data);
out:
	kfree(smb2_data);
	return rc;
}