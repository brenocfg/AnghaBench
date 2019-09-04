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
struct cifs_fid {int /*<<< orphan*/  volatile_fid; int /*<<< orphan*/  persistent_fid; } ;
typedef  int /*<<< orphan*/  FILE_ALL_INFO ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int PATH_MAX ; 
 int SMB2_query_info (unsigned int const,struct cifs_tcon*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct smb2_file_all_info*) ; 
 int /*<<< orphan*/  kfree (struct smb2_file_all_info*) ; 
 struct smb2_file_all_info* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  move_smb2_info_to_cifs (int /*<<< orphan*/ *,struct smb2_file_all_info*) ; 

__attribute__((used)) static int
smb2_query_file_info(const unsigned int xid, struct cifs_tcon *tcon,
		     struct cifs_fid *fid, FILE_ALL_INFO *data)
{
	int rc;
	struct smb2_file_all_info *smb2_data;

	smb2_data = kzalloc(sizeof(struct smb2_file_all_info) + PATH_MAX * 2,
			    GFP_KERNEL);
	if (smb2_data == NULL)
		return -ENOMEM;

	rc = SMB2_query_info(xid, tcon, fid->persistent_fid, fid->volatile_fid,
			     smb2_data);
	if (!rc)
		move_smb2_info_to_cifs(data, smb2_data);
	kfree(smb2_data);
	return rc;
}