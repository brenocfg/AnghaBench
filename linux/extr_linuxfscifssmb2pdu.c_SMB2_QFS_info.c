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
typedef  int /*<<< orphan*/  u64 ;
struct smb_rqst {int rq_nvec; struct kvec* rq_iov; } ;
struct smb2_query_info_rsp {int /*<<< orphan*/  OutputBufferLength; int /*<<< orphan*/  OutputBufferOffset; } ;
struct smb2_fs_full_size_info {int dummy; } ;
struct kvec {scalar_t__ iov_base; } ;
struct kstatfs {int dummy; } ;
struct cifs_tcon {struct cifs_ses* ses; } ;
struct cifs_ses {int dummy; } ;

/* Variables and functions */
 int CIFS_TRANSFORM_REQ ; 
 int /*<<< orphan*/  FS_FULL_SIZE_INFORMATION ; 
 int /*<<< orphan*/  SMB2_QUERY_INFO_HE ; 
 int build_qfs_info_req (struct kvec*,struct cifs_tcon*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int cifs_send_recv (unsigned int const,struct cifs_ses*,struct smb_rqst*,int*,int,struct kvec*) ; 
 int /*<<< orphan*/  cifs_small_buf_release (scalar_t__) ; 
 int /*<<< orphan*/  cifs_stats_fail_inc (struct cifs_tcon*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_rsp_buf (int,scalar_t__) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct smb_rqst*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  smb2_copy_fs_info_to_kstatfs (struct smb2_fs_full_size_info*,struct kstatfs*) ; 
 int smb2_validate_iov (int,int /*<<< orphan*/ ,struct kvec*,int) ; 
 scalar_t__ smb3_encryption_required (struct cifs_tcon*) ; 

int
SMB2_QFS_info(const unsigned int xid, struct cifs_tcon *tcon,
	      u64 persistent_fid, u64 volatile_fid, struct kstatfs *fsdata)
{
	struct smb_rqst rqst;
	struct smb2_query_info_rsp *rsp = NULL;
	struct kvec iov;
	struct kvec rsp_iov;
	int rc = 0;
	int resp_buftype;
	struct cifs_ses *ses = tcon->ses;
	struct smb2_fs_full_size_info *info = NULL;
	int flags = 0;

	rc = build_qfs_info_req(&iov, tcon, FS_FULL_SIZE_INFORMATION,
				sizeof(struct smb2_fs_full_size_info),
				persistent_fid, volatile_fid);
	if (rc)
		return rc;

	if (smb3_encryption_required(tcon))
		flags |= CIFS_TRANSFORM_REQ;

	memset(&rqst, 0, sizeof(struct smb_rqst));
	rqst.rq_iov = &iov;
	rqst.rq_nvec = 1;

	rc = cifs_send_recv(xid, ses, &rqst, &resp_buftype, flags, &rsp_iov);
	cifs_small_buf_release(iov.iov_base);
	if (rc) {
		cifs_stats_fail_inc(tcon, SMB2_QUERY_INFO_HE);
		goto qfsinf_exit;
	}
	rsp = (struct smb2_query_info_rsp *)rsp_iov.iov_base;

	info = (struct smb2_fs_full_size_info *)(
		le16_to_cpu(rsp->OutputBufferOffset) + (char *)rsp);
	rc = smb2_validate_iov(le16_to_cpu(rsp->OutputBufferOffset),
			       le32_to_cpu(rsp->OutputBufferLength), &rsp_iov,
			       sizeof(struct smb2_fs_full_size_info));
	if (!rc)
		smb2_copy_fs_info_to_kstatfs(info, fsdata);

qfsinf_exit:
	free_rsp_buf(resp_buftype, rsp_iov.iov_base);
	return rc;
}