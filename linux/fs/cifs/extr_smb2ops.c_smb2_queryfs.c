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
struct smb2_query_info_rsp {int /*<<< orphan*/  OutputBufferLength; int /*<<< orphan*/  OutputBufferOffset; } ;
struct smb2_fs_full_size_info {int dummy; } ;
struct kvec {scalar_t__ iov_base; int /*<<< orphan*/  member_1; int /*<<< orphan*/ * member_0; } ;
struct kstatfs {int /*<<< orphan*/  f_type; } ;
struct cifs_tcon {int dummy; } ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 int CIFS_NO_BUFFER ; 
 int /*<<< orphan*/  FILE_READ_ATTRIBUTES ; 
 int /*<<< orphan*/  FS_FULL_SIZE_INFORMATION ; 
 int /*<<< orphan*/  SMB2_MAGIC_NUMBER ; 
 int /*<<< orphan*/  SMB2_O_INFO_FILESYSTEM ; 
 int /*<<< orphan*/  free_rsp_buf (int,scalar_t__) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smb2_copy_fs_info_to_kstatfs (struct smb2_fs_full_size_info*,struct kstatfs*) ; 
 int smb2_query_info_compound (unsigned int const,struct cifs_tcon*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct kvec*,int*,int /*<<< orphan*/ *) ; 
 int smb2_validate_iov (int,int /*<<< orphan*/ ,struct kvec*,int) ; 

__attribute__((used)) static int
smb2_queryfs(const unsigned int xid, struct cifs_tcon *tcon,
	     struct kstatfs *buf)
{
	struct smb2_query_info_rsp *rsp;
	struct smb2_fs_full_size_info *info = NULL;
	__le16 utf16_path = 0; /* Null - open root of share */
	struct kvec rsp_iov = {NULL, 0};
	int buftype = CIFS_NO_BUFFER;
	int rc;


	rc = smb2_query_info_compound(xid, tcon, &utf16_path,
				      FILE_READ_ATTRIBUTES,
				      FS_FULL_SIZE_INFORMATION,
				      SMB2_O_INFO_FILESYSTEM,
				      sizeof(struct smb2_fs_full_size_info),
				      &rsp_iov, &buftype, NULL);
	if (rc)
		goto qfs_exit;

	rsp = (struct smb2_query_info_rsp *)rsp_iov.iov_base;
	buf->f_type = SMB2_MAGIC_NUMBER;
	info = (struct smb2_fs_full_size_info *)(
		le16_to_cpu(rsp->OutputBufferOffset) + (char *)rsp);
	rc = smb2_validate_iov(le16_to_cpu(rsp->OutputBufferOffset),
			       le32_to_cpu(rsp->OutputBufferLength),
			       &rsp_iov,
			       sizeof(struct smb2_fs_full_size_info));
	if (!rc)
		smb2_copy_fs_info_to_kstatfs(info, buf);

qfs_exit:
	free_rsp_buf(buftype, rsp_iov.iov_base);
	return rc;
}