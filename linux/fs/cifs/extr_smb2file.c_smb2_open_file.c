#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct smb2_file_all_info {scalar_t__ IndexNumber; } ;
struct network_resiliency_req {scalar_t__ Reserved; int /*<<< orphan*/  Timeout; } ;
struct cifs_open_parms {TYPE_1__* tcon; int /*<<< orphan*/  desired_access; int /*<<< orphan*/  cifs_sb; int /*<<< orphan*/  path; struct cifs_fid* fid; } ;
struct cifs_fid {int /*<<< orphan*/  volatile_fid; int /*<<< orphan*/  persistent_fid; } ;
typedef  int /*<<< orphan*/  nr_ioctl_req ;
typedef  int /*<<< orphan*/  __u8 ;
typedef  int /*<<< orphan*/  __u32 ;
typedef  struct smb2_file_all_info __le16 ;
struct TYPE_3__ {int use_resilient; int /*<<< orphan*/  handle_timeout; } ;
typedef  int /*<<< orphan*/  FILE_ALL_INFO ;

/* Variables and functions */
 int /*<<< orphan*/  CIFSMaxBufSize ; 
 int ENOMEM ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  FILE_READ_ATTRIBUTES ; 
 int /*<<< orphan*/  FSCTL_LMR_REQUEST_RESILIENCY ; 
 int /*<<< orphan*/  FYI ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int PATH_MAX ; 
 int /*<<< orphan*/  SMB2_OPLOCK_LEVEL_BATCH ; 
 int SMB2_get_srv_num (unsigned int const,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 int SMB2_ioctl (unsigned int const,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int SMB2_open (unsigned int const,struct cifs_open_parms*,struct smb2_file_all_info*,int /*<<< orphan*/ *,struct smb2_file_all_info*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VFS ; 
 struct smb2_file_all_info* cifs_convert_path_to_utf16 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cifs_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct smb2_file_all_info*) ; 
 struct smb2_file_all_info* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  move_smb2_info_to_cifs (int /*<<< orphan*/ *,struct smb2_file_all_info*) ; 

int
smb2_open_file(const unsigned int xid, struct cifs_open_parms *oparms,
	       __u32 *oplock, FILE_ALL_INFO *buf)
{
	int rc;
	__le16 *smb2_path;
	struct smb2_file_all_info *smb2_data = NULL;
	__u8 smb2_oplock;
	struct cifs_fid *fid = oparms->fid;
	struct network_resiliency_req nr_ioctl_req;

	smb2_path = cifs_convert_path_to_utf16(oparms->path, oparms->cifs_sb);
	if (smb2_path == NULL) {
		rc = -ENOMEM;
		goto out;
	}

	smb2_data = kzalloc(sizeof(struct smb2_file_all_info) + PATH_MAX * 2,
			    GFP_KERNEL);
	if (smb2_data == NULL) {
		rc = -ENOMEM;
		goto out;
	}

	oparms->desired_access |= FILE_READ_ATTRIBUTES;
	smb2_oplock = SMB2_OPLOCK_LEVEL_BATCH;

	rc = SMB2_open(xid, oparms, smb2_path, &smb2_oplock, smb2_data, NULL,
		       NULL);
	if (rc)
		goto out;


	 if (oparms->tcon->use_resilient) {
		/* default timeout is 0, servers pick default (120 seconds) */
		nr_ioctl_req.Timeout =
			cpu_to_le32(oparms->tcon->handle_timeout);
		nr_ioctl_req.Reserved = 0;
		rc = SMB2_ioctl(xid, oparms->tcon, fid->persistent_fid,
			fid->volatile_fid, FSCTL_LMR_REQUEST_RESILIENCY,
			true /* is_fsctl */,
			(char *)&nr_ioctl_req, sizeof(nr_ioctl_req),
			CIFSMaxBufSize, NULL, NULL /* no return info */);
		if (rc == -EOPNOTSUPP) {
			cifs_dbg(VFS,
			     "resiliency not supported by server, disabling\n");
			oparms->tcon->use_resilient = false;
		} else if (rc)
			cifs_dbg(FYI, "error %d setting resiliency\n", rc);

		rc = 0;
	}

	if (buf) {
		/* if open response does not have IndexNumber field - get it */
		if (smb2_data->IndexNumber == 0) {
			rc = SMB2_get_srv_num(xid, oparms->tcon,
				      fid->persistent_fid,
				      fid->volatile_fid,
				      &smb2_data->IndexNumber);
			if (rc) {
				/*
				 * let get_inode_info disable server inode
				 * numbers
				 */
				smb2_data->IndexNumber = 0;
				rc = 0;
			}
		}
		move_smb2_info_to_cifs(buf, smb2_data);
	}

	*oplock = smb2_oplock;
out:
	kfree(smb2_data);
	kfree(smb2_path);
	return rc;
}